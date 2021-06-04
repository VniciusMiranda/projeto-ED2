#include "Airport.h"


// TODO: implement automatic weather condition setting
Airport_t* create_airport(char* name, char* code, Location_t* loc) {
    if(is_null_ptr(name) || is_null_ptr(code)) return NULL;

    Airport_t* new_airport = (Airport_t*) malloc(sizeof(Airport_t));
    if(is_null_ptr(new_airport)) return NULL;

    strcpy(new_airport->name, name);
    strcpy(new_airport->code, code);

    new_airport->planes = create_list();
    new_airport->connections = create_list();
    new_airport->location = *loc;

    new_airport->id = ++LAST_VALID_ID_AIRPORT;

    new_airport->num_connections = 0;
    new_airport->num_planes = 0;

    // hardcoded test value
    new_airport->WeatherCondition = (WeatherCondition_t) SUNNY;
    
    return new_airport;
}

int dealloc_airport(void* ap_ptr){
    if(is_null_ptr(ap_ptr)) return ERR;
    log_info("dealloc_airport(): init.");

    Airport_t* ap = (Airport_t*) ap_ptr; 

    if(!is_empty_list(ap->planes)) {
        log_info("dealocating planes...");
        if(error_in(destroy_list(ap->planes, dealloc_pl))) {
            log_error("error while deallocating planes.");
            return ERR;
        }
        log_info("planes deallocated.");

    }
    
    if(!is_empty_list(ap->connections)) {
        if(error_in(destroy_list(ap->connections, dealloc_airport))) {
            log_error("error while deallocating connections.");
            return ERR;
        }
        log_info("connections deallocated.");
    }

    free(ap);

    log_info("dealloc_airport(): finish.");
    return OK;
}


int insert_connection(Airport_t* ap, unsigned long int conn_id) {
    if(!ap) return ERR;

    Airports_t result = read_airport(find_airport_by_id, &conn_id, false);
    if(is_null_ptr(result)) {
        log_error("insert_connection(): read_airport returned NULL.");
        return ERR;
    }

    if(is_empty_list(result)) {
        log_error("insert_connection(): read_airport returned an empty list.");
        return ERR;
    }

    if(result->length > 1) {
        log_error("insert_connection(): read_airport returned an more than 1 value.");
        return ERR;
    }

    for(int i = 0; i < ap->num_connections; i++) {
        if(ap->connections_id[i] == conn_id) {
            log_info("insert_connection(): connection already exists on this airport");
            return ERR;
        }
    }

    ap->connections_id[ap->num_connections++] = conn_id;
    if(insert_element(ap->connections, result->head->data) == ERR) {
        log_error("insert_connection(): error while inserting element.");
        return ERR;
    }

    return OK;
}

int insert_plane(Airport_t* ap, unsigned long int plane_id){
    if(!ap) return ERR;
    ap->planes_id[ap->num_planes++] = plane_id;
}


Connections_t get_connections(Airport_t* ap) {
    int_array_t arr;
    arr.array = ap->connections_id;
    arr.size = ap->num_connections;
    return read_airport(find_airport_by_ids, &arr, false);
}


/* data persitency functions */
int write_airport(void* ptr) {
    if(!ptr) return ERR;

    Airport_t* ap = (Airport_t*) ptr; 

    char table_path[PATH_MAX]; 
    get_airport_table_path(table_path);

    FILE* f = fopen(table_path, "ab");
    if(!f) return ERR; 

    fwrite(ap, sizeof(Airport_t), 1, f);

    fclose(f);
}

// TODO: refactor this function
int delete_airport(bool(find_func)(void*, void*), void* cmp) {
    if(!find_func) return ERR;
    log_info("delete_airport(): init.");

      Airports_t airports = read_airport(find_func, cmp, true);
    if(is_null_ptr(airports)) return ERR;

    recreate_database_table(TABLE_NAME_AIRPORT);
    if(error_in(for_each_element(airports, write_airport))) return ERR;

    return OK;
}

/*
    Read airport table and returns all aiports that satisfy the condition
    of the @find_func function and are not deleted.
    params;
    find_func
    cmp 
    return linked_list of airport
*/
Airports_t read_airport(bool(find_func)(void*, void*), void* cmp, bool not) {
    log_info("read_airport(): init.");
    char table_path[PATH_MAX]; 
    get_airport_table_path(table_path);

    FILE* f = fopen(table_path, "rb");
    if(!f) return NULL; 

    Airports_t airports = create_list();
    if(is_null_ptr(airports)) return NULL;


    while(true) {
        Airport_t* air = (Airport_t*) malloc(sizeof(Airport_t));
        if(is_null_ptr(air)) return NULL;

        fread(air, sizeof(Airport_t), 1, f);

        air->connections = NULL;
        air->planes = NULL;

        if(feof(f)) {
            dealloc_airport(air);
            break;
        }

        air->connections = create_list();
        air->planes = create_list();

        bool found_match = not ? !find_func(air, cmp) : find_func(air, cmp);
        if(found_match) {
            sprintf(LOG, "found match id: %ld", air->id);
            log_info(LOG);

            if(insert_element(airports, air) == ERR){
                log_warning("read_airport(): error while adding airports.");
            }
        }
    }
    fclose(f);

    return error_in(update_airports_connections(airports)) ? NULL : airports;   
}

int update_airport(Airport_t* new_ap, bool(*find_func)(void*, void*), void* cmp) {
    if(!new_ap ) return ERR;
    char table_path[PATH_MAX];
    get_airport_table_path(table_path);

    Airports_t airports = read_airport(all_airports, NULL, false);
    if(is_null_ptr(airports)) return ERR;

    Airports_t updated_airports = create_list();
    if(is_null_ptr(updated_airports)) return ERR;

    element_t* aux = airports->head;

    while(aux) {
        if(find_func(aux->data, cmp)) {
            new_ap->id = ((Airport_t*) aux->data)->id;
            insert_element(updated_airports, new_ap);
        } 
        else 
            insert_element(updated_airports, aux->data);
        
        aux = aux->next;
    }

    recreate_database_table(TABLE_NAME_AIRPORT);
    for_each_element(updated_airports, write_airport);

    return OK;
}

/* airport print format */
void print_airport(FILE* f, void* d, color_t color, bool is_bold) {
    Airport_t* ap = (Airport_t*) d;

    char wc[TEXT_MAX];
    getName_wc(ap->WeatherCondition, wc);

    set_color(f, color, is_bold);
    print_line(f, 80, 0);

    fprintf(f, "id: %ld\n", ap->id);
    fprintf(f, "nome do aeroporto: %s\n", ap->name);
    fprintf(f, "codigo: %s\n", ap->code);
    fprintf(f, "cidade: %s\n", ap->location.city);
    fprintf(f, "país: %s\n", ap->location.country);
    fprintf(f, "weather condition: %s\n", wc);

    fprintf(f, "numero de conexoes: %d\n", ap->num_connections);
    fprintf(f, "ids das conexoes: ");
    for(int i = 0; i < ap->num_connections; i++)
        fprintf(f, "%ld ", ap->connections_id[i]);
    fprintf(f, "\n");

    fprintf(f, "numero de avioes: %d\n", ap->num_planes);
    fprintf(f, "ids dos avioes: ");
    for(int i = 0; i < ap->num_planes; i++)
        fprintf(f, "%ld ", ap->planes_id[i]);

    fprintf(f, "\n");

    reset_color(f);
}

int update_airport_connections(void* _air) {
    if(!_air) return ERR;

    Airport_t* airport = (Airport_t*) _air; 

    if(airport->num_connections > 0) {
        int_array_t arr;
        arr.array = airport->connections_id;
        arr.size = airport->num_connections;

        airport->connections = read_airport(find_airport_by_ids, &arr, false);
        return OK;
    }

    airport->connections = create_list();

    return OK;
}

int update_airports_connections(Airports_t airports) {
    if(is_null_ptr(airports)) return ERR;
    
    return for_each_element(airports, update_airport_connections);
}

int insert_connection(Airport_t* ap,unsigned long int conn_id);

Planes_t get_airport_planes(Airport_t* airport);

int insert_plane(Airport_t* ap,unsigned long int plane_id);



long int resolve_airport_id() {
    char table_path[PATH_MAX];
    get_airport_table_path(table_path);

    Airport_t* ap = (Airport_t*) malloc(sizeof(Airport_t));
    if(!ap) return ERR;

    FILE* f = fopen(table_path, "rb");
    fseek(f, 0, SEEK_END);

    if(ftell(f) == 0) {
        free(ap);       
        LAST_VALID_ID_AIRPORT = 0;
        return LAST_VALID_ID_AIRPORT;
    }

    fseek(f, -((int)sizeof(Airport_t)), SEEK_END);
    fread(ap, sizeof(Airport_t), 1, f);

    LAST_VALID_ID_AIRPORT = ap->id;

    ap->planes = NULL;
    ap->connections = NULL;
   
    dealloc_airport(ap);
    fclose(f);

    return LAST_VALID_ID_AIRPORT;
}


int get_airport_table_path(char* dest) {
    get_database_table_path(dest, TABLE_NAME_AIRPORT);
}


/* find functions */
bool find_airport_by_name(void* d, void* cmp) {
    Airport_t* ap = (Airport_t*) d;
    char* str = (char*) cmp;
    return equals(ap->name, str); 
}

bool find_airport_by_code(void* d, void* cmp) {
    Airport_t* ap = (Airport_t*) d;
    char* code = (char* ) cmp;
    return equals(ap->code, code); 
}

bool find_airport_by_id(void* d, void* cmp) {
    Airport_t* ap = (Airport_t*) d;
    long int ID = *((long int*)cmp);
    return ap->id == ID;
}

bool find_airport_by_city(void* d, void* cmp) {
    Airport_t* ap = (Airport_t*) d;
    char* city = (char* ) cmp;
    return equals(ap->location.city, city);
}

bool find_airport_by_country(void* d, void* cmp) {
    Airport_t* ap = (Airport_t*) d;
    char* country = (char* ) cmp;
    return equals(ap->location.country, country);
}

bool find_airport_by_ids(void* d, void* cmp) {
    int_array_t* arr = (int_array_t*) cmp;
    Airport_t* ap = (Airport_t*) d;

    for(int i = 0; i < arr->size; i++)
        if(ap->id == arr->array[i])
            return true;

    return false;

}

bool all_airports(void* d, void* cmp) {
    return true;
}


int get_airport_id(void* d) {
    Airport_t* ap = (Airport_t*) d;
    return ap->id;
}

int get_airport_name(void* d) {
    Airport_t* ap = (Airport_t*) d;
    return get_first_letter_upper_case_int_repr(ap->name);
}

int get_airport_code(void* d) {
    Airport_t* ap = (Airport_t*) d;
    return get_first_letter_upper_case_int_repr(ap->code);

}

int get_airport_city(void* d) {
    Airport_t* ap = (Airport_t*) d;
    return get_first_letter_upper_case_int_repr(ap->location.city);
}

int get_airport_country(void* d){
    Airport_t* ap = (Airport_t*) d;
    return get_first_letter_upper_case_int_repr(ap->location.country);
}


     
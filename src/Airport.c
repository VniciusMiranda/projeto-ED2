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
    new_airport->deleted = false;

    new_airport->num_connections = 0;
    new_airport->num_planes = 0;

    // hardcoded test value
    new_airport->WeatherCondition = (WeatherCondition_t) SUNNY;
    
    return new_airport;
}

int dealloc_airport(void* ap_ptr){
    if(is_null_ptr(ap_ptr)) return ERR;

    Airport_t* ap = (Airport_t*) ap_ptr; 
    if(!is_empty_list(ap->planes))
        destroy_list(ap->planes, dealloc_pl);
    
    if(!is_empty_list(ap->connections))
        destroy_list(ap->connections, dealloc_airport);

    free(ap);

    return OK;
}


int insert_connection(Airport_t* ap, unsigned long int conn_id) {
    if(!ap) return ERR;
    ap->connections_id[ap->num_connections++] = conn_id;
}
int insert_plane(Airport_t* ap, unsigned long int plane_id){
    if(!ap) return ERR;
    ap->planes_id[ap->num_planes++] = plane_id;
}


Connections_t get_connections(Airport_t* ap) {
    int_array_t arr;
    arr.array = ap->connections_id;
    arr.size = ap->num_connections;
    return read_airport(find_airport_by_ids, &arr);
}


/* data persitency functions */
int write_airport(Airport_t* ap) {
    if(!ap) return ERR;

    char table_path[PATH_MAX]; 
    get_airport_table_path(table_path);

    FILE* f = fopen(table_path, "ab");
    if(!f) return ERR; 

    fwrite(ap, sizeof(Airport_t), 1, f);

    fclose(f);
}


int delete_airport(bool(find_func)(void*, void*), void* cmp) {
    if(!find_func) return ERR;

    char table_path[PATH_MAX];
    get_airport_table_path(table_path);

    FILE* f;
    int pos = 0;
    bool found_match = false;

    while(true) {

        Airport_t* ap = (Airport_t*) malloc(sizeof(Airport_t));
        if(!ap) return ERR;

        f = fopen(table_path, "rb");
        fseek(f, pos, SEEK_SET);

        if(!f) return ERR;

        fread(ap, sizeof(Airport_t), 1, f);
        if(feof(f)) {
            dealloc_airport(ap);
            break;
        }

        if(find_func(ap, cmp)) {
            found_match = true;
            fseek(f, -((int)sizeof(Airport_t)), SEEK_CUR);
            pos = ftell(f);
            fclose(f);
            ap->deleted = true;
            f = fopen(table_path, "wb");
            fseek(f, pos, SEEK_CUR);
            fwrite(ap, sizeof(Airport_t), 1, f);
            pos = ftell(f);
            fclose(f);
        }
    }

    return found_match ? OK : ERR;
}

Airports_t read_airport(bool(find_func)(void*, void*), void* cmp) {
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
        
        if(feof(f)) {
            dealloc_airport(air);
            break;
        }
        air->connections = NULL;
        air->planes = NULL;

        if(air->deleted) {
            dealloc_airport(air);
            continue;
        }

        if(find_func(air, cmp))
            if(insert_element(airports, air) == ERR)
                log_error("error while reading airports");
    }

    fclose(f);
    return airports;   
}

int update_airport(Airport_t* new_ap, bool(*find_func)(void*, void*), void* cmp) {
    if(!new_ap ) return ERR;
    char table_path[PATH_MAX];
    get_airport_table_path(table_path);

    FILE* f;
    int pos = 0;
    bool found_match = false;
    while(true) {

        Airport_t* ap = (Airport_t*) malloc(sizeof(Airport_t));
        if(!ap) return ERR;

        f = fopen(table_path, "rb");
        fseek(f, pos, SEEK_SET);

        if(!f) return ERR;

        fread(ap, sizeof(Airport_t), 1, f);
        if(feof(f)) {
            dealloc_airport(ap);
            break;
        }

        if(find_func(ap, cmp)) {
            found_match = true;
            fseek(f, -((int)sizeof(Airport_t)), SEEK_CUR);
            pos = ftell(f);
            fclose(f);
            ap->deleted = true;
            f = fopen(table_path, "wb");
            fseek(f, pos, SEEK_CUR);
            fwrite(new_ap, sizeof(Airport_t), 1, f);
            pos = ftell(f);
            fclose(f);
        }
    }

    return found_match ? OK : ERR;
}


/* airport print format */
void print_airport(FILE* f, void* d, color_t color, bool is_bold) {
    Airport_t* ap = (Airport_t*) d;

    if(!ap->deleted) {

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
    }

    reset_color(f);
}


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
    int ID = *((int*)cmp);
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
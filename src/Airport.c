#include "Airport.h"

unsigned long int LAST_VALID_ID_AIRPORT;

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

int write_airport(Airport_t* ap) {
    if(!ap) return ERR;

    char table_path[PATH_MAX]; 
    get_airport_table_path(table_path);

    FILE* f = fopen(table_path, "ab");
    if(!f) return ERR; 

    fwrite(ap, sizeof(Airport_t), 1, f);

    fclose(f);
}

Airports_t read_all_airports() {
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

        if(insert_element(airports, air) == ERR)
            log_error("error while reading airports");
    }

    fclose(f);
    return airports;
}

int update_airport(Airport_t* new_ap, unsigned long int id) {
    if(!new_ap || !id) return ERR;
    char table_path[PATH_MAX];
    get_airport_table_path(table_path);

    while(true) {

    }
}

bool find_airport_by_name(void* d, void* cmp) {
    Airport_t* ap = (Airport_t*) d, *cmp_ap = (Airport_t*) cmp;
    return equals(ap->name, cmp_ap->name); 
}

bool find_airport_by_code(void* d, void* cmp) {
    Airport_t* ap = (Airport_t*) d, *cmp_ap = (Airport_t*) cmp;
    return equals(ap->code, cmp_ap->code); 
}

int get_airport_table_path(char* dest) {
    get_database_table_path(dest, TABLE_NAME_AIRPORT);
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


void print_airport(FILE* f, void* d, color_t color, bool is_bold) {
    Airport_t* ap = (Airport_t*) d;

    char wc[TEXT_MAX];
    getName_wc(ap->WeatherCondition, wc);

    set_color(f, color, is_bold);
    print_line(LOG_FILE, 0, 0);
    fprintf(LOG_FILE, "id: %ld\n", ap->id);
    fprintf(LOG_FILE, "nome do aeroporto: %s\n", ap->name);
    fprintf(LOG_FILE, "codigo: %s\n", ap->code);
    fprintf(LOG_FILE, "cidade: %s\n", ap->location.city);
    fprintf(LOG_FILE, "país: %s\n", ap->location.country);
    fprintf(LOG_FILE, "weather condition: %s\n", wc);

    reset_color(f);
}

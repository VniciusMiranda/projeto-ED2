#include "Airport.h"

Airport_t* create_ap(char* name, char* code, Location_t* loc, WeatherCondition_t* wc) {

}

int write_ap(Airport_t* ap) {
    if(!ap) return ERR;

    char table_path[PATH_MAX]; 
    getTablePath_ap(table_path);

    FILE* f = fopen(table_path, "a");
    if(!f) return ERR; 
    fwrite(ap, sizeof(ap), 1, f);
    fclose(f);
}

bool find_airport_by_name(void* d, void* cmp) {
    Airport_t* ap = (Airport_t*) d, *cmp_ap = (Airport_t*) cmp;
    return equals(ap->name, cmp_ap->name); 
}

bool find_airport_by_code(void* d, void* cmp) {
    Airport_t* ap = (Airport_t*) d, *cmp_ap = (Airport_t*) cmp;
    return equals(ap->code, cmp_ap->code); 
}

int getTablePath_ap(char* dest) {
    getTablePath_db(dest, TABLE_NAME_AP);
}


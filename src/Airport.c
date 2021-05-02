#include "Airport.h"

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

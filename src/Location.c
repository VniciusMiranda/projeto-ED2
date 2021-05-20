#include "Location.h"

Location_t* create_loc(char* city, char* country) {
    if(is_null_ptr(city) || is_null_ptr(country)) return NULL;

    Location_t* new_loc = (Location_t*) malloc(sizeof(Location_t));
    if(is_null_ptr(new_loc)) return NULL;

    strcpy(new_loc->city, city);
    strcpy(new_loc->country, country);

    return new_loc;
}

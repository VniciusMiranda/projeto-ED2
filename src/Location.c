#include "Location.h"

Location_t* create_location(char* city, char* country) {
    if(is_null_ptr(city) || is_null_ptr(country)) return NULL;

    Location_t* new_loc = (Location_t*) malloc(sizeof(Location_t));
    if(is_null_ptr(new_loc)) return NULL;

    strcpy(new_loc->city, city);
    strcpy(new_loc->country, country);

    return new_loc;
}

Location_t* get_location(struct json_object* json) {
    struct json_object* city_name, *sys, *country;

    Location_t* location = (Location_t*) malloc(sizeof(Location_t));
    if(!location) return NULL;

    json_object_object_get_ex(json, "name", &city_name);
    json_object_object_get_ex(json, "sys", &sys);
    json_object_object_get_ex(sys, "country", &country);

    strcpy(location->city, json_object_get_string(city_name));
    strcpy(location->country, json_object_get_string(country));

    return location;
}

int copy_location(Location_t* dest, Location_t* src) {
    if(!dest || !src) return ERR;

    strcpy(dest->city, src->city);
    strcpy(dest->country, src->country);
    return OK;
}

int destroy_location(Location_t* loc) {
    if(!loc) return ERR;
    free(loc);
    return OK;
}

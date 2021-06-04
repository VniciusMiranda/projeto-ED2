#ifndef _LOCATION_H_
#define _LOCATION_H_

#define CITY_NAME_MAX 300
#define COUNTRY_NAME_MAX 300 

#include <json-c/json.h>

#include "utils.h"

typedef struct location { 
    char city[CITY_NAME_MAX];
    char country[COUNTRY_NAME_MAX];
} Location_t;

Location_t* create_location(char* city, char* country);

Location_t* get_location(struct json_object* json);

int copy_location(Location_t* dest, Location_t* src);

int destroy_location(Location_t* loc);

#endif
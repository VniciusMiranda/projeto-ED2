#ifndef _AIRPORT_H_
#define _AIRPORT_H_

#define AIRPORT_NAME_MAX 1000
#define AIRPORT_CODE_MAX 10

#include "linked_list.h"

#include "Location.h"
#include "WeatherCondition.h"

typedef linked_list_t* Planes_t;
typedef linked_list_t* Connections_t;

typedef struct Airport {
    long int id;
    char* name[AIRPORT_NAME_MAX];
    char* code[AIRPORT_CODE_MAX];
    Location_t* location;
    Planes_t planes; // planes are not implemented yet
    Connections_t connections; // stores type Airport
    WeatherCondition_t* WeatherCondition;
} Airport_t;

#endif

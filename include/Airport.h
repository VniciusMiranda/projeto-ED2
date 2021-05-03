#ifndef _AIRPORT_H_
#define _AIRPORT_H_

#define AIRPORT_NAME_MAX 1000
#define AIRPORT_CODE_MAX 10

#include "linked_list.h"

#include "Database.h"
#include "log.h"

#include "Location.h"
#include "WeatherCondition.h"
#include "Plane.h"

#define TABLE_NAME_AP "airport"

typedef linked_list_t* Connections_t;


typedef struct Airport {
    long int id;
    char name[AIRPORT_NAME_MAX];
    char code[AIRPORT_CODE_MAX];
    Location_t* location;
    Planes_t planes; 

    /* linked list of airports */
    Connections_t connections;
    WeatherCondition_t* WeatherCondition;
} Airport_t;

typedef linked_list_t* Airports_t;

Airport_t* create_ap(char* name, char* code, Location_t* loc, WeatherCondition_t* wc);

int destroy_ap(Airport_t* ap);

/* search functions */
bool find_airport_by_name(void* d, void* cmp);

bool find_airport_by_code(void* d, void* cmp);

/* data persitance functions */
int write_ap(Airport_t* ap);

Airports_t read_ap();

int init_ap_table();

int getTablePath_ap();

#endif

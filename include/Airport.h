#ifndef _AIRPORT_H_
#define _AIRPORT_H_

#define AIRPORT_NAME_MAX 1000
#define AIRPORT_CODE_MAX 10

#include "linked_list.h"

#include "Database.h"
#include "log.h"

#include "WeatherCondition.h"
#include "Location.h"
#include "Plane.h"

#define TABLE_NAME_AIRPORT "airport"

typedef linked_list_t* Connections_t;


typedef struct Airport {
    unsigned long int id;
    bool deleted;
    char name[AIRPORT_NAME_MAX];
    char code[AIRPORT_CODE_MAX];
    Location_t location;
    Planes_t planes; 

    /* linked list of airports */
    Connections_t connections;
    WeatherCondition_t WeatherCondition;

    /* foreign keys */
    unsigned long int connections_id[MAX_FOREIGN_KEY];
    unsigned long int planes_id[MAX_FOREIGN_KEY];
} Airport_t;

typedef linked_list_t* Airports_t;

Airport_t* create_airport(char* name, char* code, Location_t* loc);

int dealloc_airport(void* ap_ptr);

void print_airport(FILE* f, void* d, color_t color, bool is_bold);

/* search functions */
bool find_airport_by_name(void* d, void* cmp);

bool find_airport_by_code(void* d, void* cmp);

/* data persitance functions */

int write_airport(Airport_t* ap);

Airport_t* read_airport(unsigned long int id);

Airports_t read_all_airports();

Airports_t search_airport(bool(find_func)(void*, void*), void* cmp);

int delete_airport(bool(find_func)(void*, void*), void* cmp);

int update_airport(Airport_t* new_ap, unsigned long int id);

int init_airport_table();

long int resolve_airport_id();

int get_airport_table_path();

#endif

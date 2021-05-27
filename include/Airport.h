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

unsigned long int LAST_VALID_ID_AIRPORT;

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
    int num_connections;

    unsigned long int planes_id[MAX_FOREIGN_KEY];
    int num_planes;

} Airport_t;

typedef linked_list_t* Airports_t;

Airport_t* create_airport(char* name, char* code, Location_t* loc);

int dealloc_airport(void* ap_ptr);

void print_airport(FILE* f, void* d, color_t color, bool is_bold);

int insert_connection(Airport_t* ap,unsigned long int conn_id);

int insert_plane(Airport_t* ap,unsigned long int plane_id);

Connections_t get_connections(Airport_t* ap);

Planes_t get_planes();

/* search functions */
bool find_airport_by_name(void* d, void* cmp);

bool find_airport_by_code(void* d, void* cmp);

bool find_airport_by_id(void* d, void* cmp);

bool find_airport_by_ids(void* d, void* cmp);

bool find_airport_by_city(void* d, void* cmp);

bool find_airport_by_country(void* d, void* cmp);

bool all_airports(void* d, void* cmp);


/* sorting attr functions */
int get_airport_id(void* d);

int get_airport_name(void* d);

int get_airport_code(void* d);

int get_airport_city(void* d);

int get_airport_country(void* d);

/* data persitance functions */

int write_airport(Airport_t* ap);


Airports_t read_airport(bool(find_func)(void*, void*), void* cmp);

int delete_airport(bool(find_func)(void*, void*), void* cmp);

int update_airport(Airport_t* new_ap, bool(find_func)(void*, void*), void* cmp);

int init_airport_table();

long int resolve_airport_id();

int get_airport_table_path();

#endif

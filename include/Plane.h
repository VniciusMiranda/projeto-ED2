#ifndef _PLANE_H_
#define _PLANE_H_ 

#include "linked_list.h"
#include "AirlineCompany.h"
#include "Database.h"
#include "log.h"

#define PLANE_MODEL_MAX 32

#define TABLE_NAME_PLANE "plane"

unsigned long int LAST_VALID_ID_PLANE;

typedef enum plane_model {
    Airbus_A320 = 1,
    Boeing_737,
    DC_9MD_80,
    Boeing_777,
    Bombardier_CRJ_Series,
    Embraer_E_Jets,
    Boeing_727,
    Airbus_A330,
    Boeing_747,
    Boeing_787
} plane_model_t;

typedef struct plane {
    bool deleted;
    unsigned long int id;
    plane_model_t model;
    AirlineCompany_t airlineCompany;
    int capacity;
} Plane_t;

typedef linked_list_t* Planes_t;

Plane_t* create_plane(char* model, int capacity, AirlineCompany_t airline_company);

int dealloc_pl(void* pl_ptr);

void print_plane(FILE* f, void* d, color_t color, bool is_bold);

/* search functions */

bool find_plane_by_model(void* d, void* cmp);

bool find_plane_by_company(void* d, void* cmp);

bool find_plane_by_id(void* d, void* cmp);

bool find_plane_by_capacity(void* d, void* cmp);

bool all_planes(void* d, void* cmp);

/* sorting attr functions */

int get_plane_id(void* d);

int get_plane_model(void* d);

int get_plane_capacity(void* d);

int get_plane_company(void* d);

/* data persitance functions */

int write_plane(Plane_t* ap);

Planes_t read_plane(bool(find_func)(void*, void*), void* cmp);

Planes_t read_all_planes();

int delete_plane(bool(find_func)(void*, void*), void* cmp);

int update_plane(Plane_t* new_pl, bool(*find_func)(void*, void*), void* cmp);

int init_planes_table();

long int resolve_planes_id();

int get_plane_table_path(char* dest);

#endif 
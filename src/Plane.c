#include "Plane.h"

int get_name_model(plane_model_t model, char* dest) {

    switch(model) {
        case Airbus_A320:
            strcpy(dest, "Airbus_A320");
            break;
        case Boeing_737:
           strcpy(dest, "Boeing_737");
            break;
        case DC_9MD_80:
            strcpy(dest, "DC_9MD_80");
            break;
        case Boeing_777:
            strcpy( dest, "Boeing_777");
            break;
        case Bombardier_CRJ_Series:
            strcpy(dest,"Bombardier_CRJ_Series");
            break;
        case Embraer_E_Jets:
            strcpy(dest,"Embraer_E_Jets");
            break;
        case Boeing_727:
            strcpy(dest,"Boeing_727");

        case Airbus_A330:
            strcpy(dest, "Airbus_A330");
            break;
        case Boeing_747:
            strcpy(dest,"Boeing_747" );
            break;
        case Boeing_787:
            strcpy(dest,"Boeing_747");
            break;
        default:
            strcpy(dest,"NULL");
    }

    return OK;
}


Plane_t* create_plane(int capacity, AirlineCompany_t airline_company, plane_model_t model){
    if( capacity < 1) return NULL;

    Plane_t* new_plane = (Plane_t*) malloc(sizeof(Plane_t));
    if(is_null_ptr(new_plane)) return NULL;


    new_plane->model = model;
    new_plane->capacity = capacity;
    new_plane->id = ++LAST_VALID_ID_PLANE;

    new_plane->airlineCompany = airline_company; 
    return new_plane;
}

int dealloc_pl(void* pl_ptr) {
    if(is_null_ptr(pl_ptr)) return ERR;
    free(pl_ptr);
    return OK;  
}

void print_plane(FILE* f, void* d, color_t color, bool is_bold) {
    Plane_t* pl = (Plane_t*) d;

    set_color(f, color, is_bold);
    print_line(f, 0, 0);

    char model[TEXT_MAX];
    get_name_model(pl->model, model);

    fprintf(f, "id: %ld\n", pl->id);
    fprintf(f, "modelo: %s\n", model);
    fprintf(f, "companhia aerea: %s\n", pl->airlineCompany.name);
    fprintf(f, "capacidade: %d\n", pl->capacity);

    reset_color(f);
}

bool find_plane_by_model(void* d, void* cmp) {
    Plane_t* pl = (Plane_t*) d;
    plane_model_t* pm = (plane_model_t*) cmp;
    return pl->model == *pm; 
}

int write_plane(Plane_t* pl) {
    if(!pl) return ERR;

    char table_path[PATH_MAX]; 
    get_plane_table_path(table_path);

    FILE* f = fopen(table_path, "ab");
    if(!f) return ERR; 

    fwrite(pl, sizeof(Plane_t), 1, f);

    fclose(f);
}

Planes_t read_all_planes() {
    char table_path[PATH_MAX]; 
    get_plane_table_path(table_path);

    FILE* f = fopen(table_path, "rb");
    if(!f) return NULL; 

    Planes_t planes = create_list();
    if(is_null_ptr(planes)) return NULL;

    while(true) {
        Plane_t* pl = (Plane_t*) malloc(sizeof(Plane_t));
        if(is_null_ptr(pl)) return NULL;

        fread(pl, sizeof(Plane_t), 1, f);
        
        if(feof(f)) {
            dealloc_pl(pl);
            break;
        }

        if(insert_element(planes, pl) == ERR)
            log_error("error while reading planes");
    }

    fclose(f);
    return planes;
}

int update_plane(Plane_t* new_pl, unsigned long int id) {
    if(!new_pl || !id) return ERR;
    char table_path[PATH_MAX];
    get_plane_table_path(table_path);

    FILE* f = fopen(table_path, "rb");
    fseek(f, 0, SEEK_END);
    fseek(f, -((int)sizeof(Plane_t)), SEEK_END);
    

}

int get_plane_table_path(char* dest) {
    get_database_table_path(dest, TABLE_NAME_PLANE);
}

long int resolve_plane_id() {
    char table_path[PATH_MAX];
    get_plane_table_path(table_path);

    Plane_t* pl = (Plane_t*) malloc(sizeof(Plane_t));
    if(!pl) return ERR;

    FILE* f = fopen(table_path, "rb");
    fseek(f, 0, SEEK_END);

    if(ftell(f) == 0) {
        free(pl);       
        LAST_VALID_ID_PLANE = 0;
        return LAST_VALID_ID_PLANE;
    }

    fseek(f, -((int)sizeof(Plane_t)), SEEK_END);
    fread(pl, sizeof(Plane_t), 1, f);

    LAST_VALID_ID_PLANE = pl->id;
   
    dealloc_pl(pl);
    fclose(f);

    return LAST_VALID_ID_PLANE;
}
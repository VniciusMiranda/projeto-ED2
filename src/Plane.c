#include "Plane.h"

unsigned long int LAST_VALID_ID_PLANE;

Plane_t* create_plane(char* model, int capacity, AirlineCompanies_t companies){
    if(is_null_ptr(model) || capacity < 1) return NULL;

    Plane_t* new_plane = (Plane_t*) malloc(sizeof(Plane_t));
    if(is_null_ptr(new_plane)) return NULL;

    AirlineCompany_t* comp = (AirlineCompany_t*)find_element(companies, find_company_by_model, model);

    strcpy(new_plane->model, model);
    new_plane->capacity = capacity;
    new_plane->airlineCompany = *comp;
    new_plane->id = ++LAST_VALID_ID_PLANE;

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
    print_line(LOG_FILE, 0, 0);
    fprintf(LOG_FILE, "id: %ld\n", pl->id);
    fprintf(LOG_FILE, "modelo: %s\n", pl->model);
    fprintf(LOG_FILE, "companhia aerea: %s\n", pl->airlineCompany.name);
    fprintf(LOG_FILE, "capacidade: %s\n", pl->capacity);

    reset_color(f);
}

bool find_plane_by_model(void* d, void* cmp) {
    Plane_t* pl = (Plane_t*) d, *cmp_pl = (Plane_t*) cmp;
    return equals(pl->model, cmp_pl->model); 
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
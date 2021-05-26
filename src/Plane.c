#include "Plane.h"

Plane_t* create_plane(char* model, int capacity, AirlineCompany_t airline_company){
    if(is_null_ptr(model) || capacity < 1){
        log_error("create_plane(): Null pointer!");
        return NULL;
    }

    Plane_t* new_plane = (Plane_t*) malloc(sizeof(Plane_t));
    if(is_null_ptr(new_plane)) return NULL;

    strcpy((char*)new_plane->model, model);
    new_plane->capacity = capacity;
    new_plane->id = ++LAST_VALID_ID_PLANE;
    new_plane->deleted = false;
    new_plane->airlineCompany = airline_company; 
    return new_plane;
}

int dealloc_pl(void* pl_ptr) {
    if(is_null_ptr(pl_ptr)){
        log_error("dealloc_pl(): Null pointer!");
        return NULL;
    }
    free(pl_ptr);
    return OK;  
}

void print_plane(FILE* f, void* d, color_t color, bool is_bold) {
    Plane_t* pl = (Plane_t*) d;

    if(!pl->deleted) {
        set_color(f, color, is_bold);
        print_line(LOG_FILE, 0, 0);
        fprintf(LOG_FILE, "id: %ld\n", pl->id);
        fprintf(LOG_FILE, "modelo: %s\n", pl->model);
        fprintf(LOG_FILE, "companhia aerea: %s\n", pl->airlineCompany.name);
        fprintf(LOG_FILE, "capacidade: %s\n", pl->capacity);
    }else{
        log_warning("print_plane(): the struct has been deleted");
    }
    reset_color(f);
}

bool find_plane_by_model(void* d, void* cmp) {
    Plane_t* pl = (Plane_t*) d;
    plane_model_t* pm = (plane_model_t*) cmp;
    return pl->model == *pm; 
}

bool find_plane_by_company(void* d, void* cmp){
    Plane_t* pl = (Plane_t*) d;
    char* name = (char* ) cmp;
    return equals(pl->airlineCompany.name, name);
}

bool find_plane_by_id(void* d, void* cmp){
    Plane_t* pl = (Plane_t*) d;
    int ID = *((int*)cmp);
    return pl->id == ID;
}

bool find_plane_by_capacity(void* d, void* cmp){
    Plane_t* pl = (Plane_t*) d;
    int cap = *((int*)cmp);
    return pl->capacity == cap;
}

int get_plane_id(void* d){
    Plane_t* pl = (Plane_t*) d;
    return pl->id;
}

int get_plane_model(void* d){ 
    Plane_t* pl = (Plane_t*) d;
    char str[32];
    get_name_model(pl->model, str);
    return get_first_letter_upper_case_int_repr(str);
}

int get_plane_capacity(void* d){
    Plane_t* pl = (Plane_t*) d;
    return pl->capacity;
}

int get_plane_company(void* d){
    Plane_t* pl = (Plane_t*) d;
    return get_first_letter_upper_case_int_repr(pl->airlineCompany.name);
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

Planes_t read_plane(bool(find_func)(void*, void*), void* cmp) {
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

        if(pl->deleted) {
            dealloc_pl(pl);
            continue;
        }

        if(find_func(pl, cmp))
            if(insert_element(planes, pl) == ERR)
                log_error("error while reading planes");
    }

    fclose(f);
    return planes;   
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


int delete_plane(bool(find_func)(void*, void*), void* cmp) {
    if(!find_func) return ERR;

    char table_path[PATH_MAX];
    get_plane_table_path(table_path);

    FILE* f;
    int pos = 0;
    bool found_match = false;

    while(true) {

        Plane_t* pl = (Plane_t*) malloc(sizeof(Plane_t));
        if(!pl) return ERR;

        f = fopen(table_path, "rb");
        fseek(f, pos, SEEK_SET);

        if(!f) return ERR;

        fread(pl, sizeof(Plane_t), 1, f);
        if(feof(f)) {
            dealloc_pl(pl);
            break;
        }

        if(find_func(pl, cmp)) {
            found_match = true;
            fseek(f, -((int)sizeof(Plane_t)), SEEK_CUR);
            pos = ftell(f);
            fclose(f);
            pl->deleted = true;
            f = fopen(table_path, "wb");
            fseek(f, pos, SEEK_CUR);
            fwrite(pl, sizeof(Plane_t), 1, f);
            pos = ftell(f);
            fclose(f);
        }
    }

    return found_match ? OK : ERR;
}

int update_plane(Plane_t* new_pl, bool(*find_func)(void*, void*), void* cmp) {
    if(!new_pl ) return ERR;
    char table_path[PATH_MAX];
    get_plane_table_path(table_path);

    FILE* f;
    int pos = 0;
    bool found_match = false;
    while(true) {

        Plane_t* pl = (Plane_t*) malloc(sizeof(Plane_t));
        if(!pl) return ERR;

        f = fopen(table_path, "rb");
        fseek(f, pos, SEEK_SET);

        if(!f) return ERR;

        fread(pl, sizeof(Plane_t), 1, f);
        if(feof(f)) {
            dealloc_plane(pl);
            break;
        }

        if(find_func(pl, cmp)) {
            found_match = true;
            fseek(f, -((int)sizeof(Plane_t)), SEEK_CUR);
            pos = ftell(f);
            fclose(f);
            pl->deleted = true;
            f = fopen(table_path, "wb");
            fseek(f, pos, SEEK_CUR);
            fwrite(new_pl, sizeof(Plane_t), 1, f);
            pos = ftell(f);
            fclose(f);
        }
    }

    return found_match ? OK : ERR;
}


bool all_planes(void* d, void* cmp) {
    return true;
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
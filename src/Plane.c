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


Plane_t* create_plane(int capacity, AirlineCompany_t airline_company, char* model){
    if( capacity < 1) return NULL;

    Plane_t* new_plane = (Plane_t*) malloc(sizeof(Plane_t));
    if(is_null_ptr(new_plane)) return NULL;

    strcpy(new_plane->model, model);
    new_plane->capacity = capacity;
    new_plane->id = ++LAST_VALID_ID_PLANE;
    new_plane->deleted = false;
    new_plane->airlineCompany = airline_company; 
    return new_plane;
}

int dealloc_pl(void* pl_ptr) {
    if(is_null_ptr(pl_ptr)){
        log_error("dealloc_pl(): Null pointer!");
        return ERR;
    }
    free(pl_ptr);
    return OK;  
}

void print_plane(FILE* f, void* d, color_t color, bool is_bold) {
    Plane_t* pl = (Plane_t*) d;

    set_color(f, color, is_bold);
    print_line(f, 0, 0);


    fprintf(f, "id: %ld\n", pl->id);
    fprintf(f, "modelo: %s\n", pl->model);
    fprintf(f, "companhia aerea: %s\n", pl->airlineCompany.name);
    fprintf(f, "capacidade: %d\n", pl->capacity);

    reset_color(f);
}

bool find_plane_by_model(void* d, void* cmp) {
    Plane_t* pl = (Plane_t*) d;
    char* model = (char*) cmp;
    return equals(pl->model, model);
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
    return get_first_letter_upper_case_int_repr(pl->model);
}

int get_plane_capacity(void* d){
    Plane_t* pl = (Plane_t*) d;
    return pl->capacity;
}

int get_plane_company(void* d){
    Plane_t* pl = (Plane_t*) d;
    return get_first_letter_upper_case_int_repr(pl->airlineCompany.name);
}

int write_plane(void* pl) {
    if(!pl) return ERR;

    Plane_t* plane = (Plane_t*) pl;

    char table_path[PATH_MAX]; 
    get_plane_table_path(table_path);

    FILE* f = fopen(table_path, "ab");
    if(!f) return ERR; 

    fwrite(plane, sizeof(Plane_t), 1, f);

    fclose(f);
}

Planes_t read_plane(bool(find_func)(void*, void*), void* cmp, bool not) {
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
        bool found_match = not ? !find_func(pl, cmp) : find_func(pl, cmp);
        if(found_match)
            if(insert_element(planes, pl) == ERR)
                log_error("error while reading planes");
    }

    fclose(f);
    return planes;   
}


int delete_plane(bool(find_func)(void*, void*), void* cmp) {
    if(!find_func) return ERR;
    log_info("delete_plane(): init.");

    Planes_t planes = read_plane(find_func, cmp,true);
    if(is_null_ptr(planes)) return ERR;

    recreate_database_table(TABLE_NAME_PLANE);
    if(error_in(for_each_element(planes, write_plane))) return ERR;

    return OK;
}

int update_plane(Plane_t* new_pl, bool(*find_func)(void*, void*), void* cmp) {
    if(!new_pl) return ERR;
    char table_path[PATH_MAX];
    get_plane_table_path(table_path);

    Planes_t planes = read_plane(all_registers, NULL, false);
    if(is_null_ptr(planes)) return ERR;

    Planes_t updated_planes = create_list();
    if(is_null_ptr(updated_planes)) return ERR;

    element_t* aux = planes->head;
    Plane_t* plane_aux;

    while(aux) {
        if(find_func(aux->data, cmp)) {
            plane_aux = ((Plane_t*) aux->data);
            new_pl->id = plane_aux->id;
            insert_element(updated_planes, new_pl);
        } 
        else 
            insert_element(updated_planes, aux->data);
        
        aux = aux->next;
    }

    recreate_database_table(TABLE_NAME_PLANE);
    for_each_element(updated_planes, write_plane);

    return OK;
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
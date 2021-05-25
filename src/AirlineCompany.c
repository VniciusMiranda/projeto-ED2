#include "AirlineCompany.h"

AirlineCompany_t* create_company(char* name, char* country){
    if(is_null_ptr(name) || is_null_ptr(country)) return NULL;

    AirlineCompany_t* new_company = (AirlineCompany_t*) malloc(sizeof(AirlineCompany_t));
    if(is_null_ptr(new_company)) return NULL;

    strcpy(new_company->name, name);
    strcpy(new_company->country, country);
    new_company->planes = create_list();

    return new_company;
}

int dealloc_airCom(void* airCom_ptr) {
    if(is_null_ptr(airCom_ptr)) return ERR;

    AirlineCompany_t* comp = (AirlineCompany_t*) airCom_ptr; 
    if(!is_empty_list(comp->planes))
        destroy_list(comp->planes, dealloc_pl);
    
    free(airCom_ptr);
    return OK;  
}

void print_company(FILE* f, void* d, color_t color, bool is_bold) {
    AirlineCompany_t* comp = (AirlineCompany_t*) d;

    set_color(f, color, is_bold);
    print_line(LOG_FILE, 0, 0);
    fprintf(LOG_FILE, "nome: %ld\n", comp->name);
    fprintf(LOG_FILE, "id: %s\n", comp->id);
    fprintf(LOG_FILE, "pais: %s\n", comp->country);
    fprintf(LOG_FILE, "planes: \n");

    Plane_t* plane = (Plane_t *)comp->planes->head;

    for(int i = 0; i < comp->planes->length; i++){
        if(plane->airlineCompany.id == comp->id)
            fprintf(LOG_FILE, "%d: %s\n", i,plane->model);
    }
    reset_color(f);
}

bool find_company_by_name(void* d, void* cmp){
    AirlineCompany_t* comp = (AirlineCompany_t*) d, *cmp_comp = (AirlineCompany_t*) cmp;
    return equals(comp->name, cmp_comp->name); 
}

bool find_company_by_model(void* d, void* model) {
    AirlineCompany_t* comp = (AirlineCompany_t*) d;
    Plane_t* plane = (Plane_t *)comp->planes->head;
    return equals(plane->model, model); 
}
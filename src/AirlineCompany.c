#include "AirlineCompany.h"

AirlineCompany_t* create_company(char* name, char* country){
    if(is_null_ptr(name) || is_null_ptr(country)) return NULL;

    AirlineCompany_t* new_company = (AirlineCompany_t*) malloc(sizeof(AirlineCompany_t));
    if(is_null_ptr(new_company)) return NULL;

    strcpy(new_company->name, name);
    strcpy(new_company->country, country);

    return new_company;
}

int dealloc_airCom(void* airCom_ptr) {
    if(is_null_ptr(airCom_ptr)) return ERR;
    free(airCom_ptr);
    return OK;  
}

void print_company(FILE* f, void* d, color_t color, bool is_bold) {
    AirlineCompany_t* comp = (AirlineCompany_t*) d;

    set_color(f, color, is_bold);
    print_line(f, 0, 0);
    fprintf(f, "nome: %s\n", comp->name);
    fprintf(f, "pais: %s\n", comp->country);

    reset_color(f);
}

bool find_company_by_name(void* d, void* cmp){
    AirlineCompany_t* comp = (AirlineCompany_t*) d, *cmp_comp = (AirlineCompany_t*) cmp;
    return equals(comp->name, cmp_comp->name); 
}

#ifndef _AIRLINECOMPANY_H_
#define _AIRLINECOMPANY_H_

#define COMPANY_NAME_MAX 128

#include "linked_list.h"
#include "log.h"
#include "Location.h"

typedef struct AirlineCompany {
    char name[COMPANY_NAME_MAX];
    char country[COUNTRY_NAME_MAX];
} AirlineCompany_t;

typedef linked_list_t* AirlineCompanies_t;

AirlineCompany_t* create_company(char* name, char* country);

int dealloc_airCom(void* airCom_ptr);

void print_company(FILE* f, void* d, color_t color, bool is_bold);

bool find_company_by_name(void* d, void* cmp);
#endif

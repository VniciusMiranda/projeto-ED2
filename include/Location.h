#ifndef _LOCATION_H_
#define _LOCATION_H_

#define CITY_NAME_MAX 300
#define COUNTRY_NAME_MAX 300 

typedef struct location { 
    char* city[CITY_NAME_MAX];
    char* country[COUNTRY_NAME_MAX];
} Location_t;


#endif
#ifndef _WEATHER_CONDITION_H_
#define _WEATHER_CONDITION_H_


#include <json-c/json.h>

#include "open_weather.h"

#include "utils.h"
#include "https.h"
#include "log.h"

typedef struct weather {
    char main[TEXT_MAX];
    char description[TEXT_MAX];

    double temperature;
} Weather_t;


Weather_t* get_wether(struct json_object* json);

int print_weather(FILE* f, Weather_t* weather);

int copy_weather(Weather_t* dest, Weather_t* src); 

int update_weather(Weather_t* weather, char* city);

int destroy_weather(Weather_t* weather);

#endif
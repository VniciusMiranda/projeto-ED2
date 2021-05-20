#ifndef _WEATHER_CONDITION_H_
#define _WEATHER_CONDITION_H_

#include "utils.h"
#include "https.h"
#include "log.h"

// just for testing 

#define API_KEY "< api key >"
#define API_URL "https://api.openweathermap.org/data/2.5/weather"


typedef enum condition { 
    NOT_FOUND,
    CALM,
    SUNNY,
    FOGGY,
    WINDY,
    RAINY,
    STORMY,
    CLEAR,
} WeatherCondition_t;

WeatherCondition_t getWetherCondition(char* city_name);

int destroyWeatherCondition(WeatherCondition_t* wc);

int getName_wc(WeatherCondition_t wc, char* dest);

#endif
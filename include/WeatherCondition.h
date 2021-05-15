#ifndef _WEATHER_CONDITION_H_
#define _WEATHER_CONDITION_H_

#include "utils.h"
#include "https.h"
#include "log.h"

// just for testing 
#define API_KEY "<Open Weather KEY>"
#define API_URL "https://api.openweathermap.org/data/2.5/weather"


typedef enum condition { 
    RAINY,
    FOGGY,
    CALM,
    WINDY,
    STORMY,
    SUNNY,
} WeatherCondition_t;

WeatherCondition_t* getWetherCondition(char* city_name);

int destroyWeatherCondition(WeatherCondition_t* wc);


#endif
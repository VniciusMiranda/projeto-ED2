#ifndef _OPEN_WEATHER_H_
#define _OPEN_WEATHER_H_

#include <json-c/json.h>

#include "utils.h"
#include "https.h"
#include "log.h"

// just for testing 

#define API_KEY ""
#define API_URL "https://api.openweathermap.org/data/2.5/weather"

/*
RESPONSE FORMAT

{
  "coord": { "lon": -49.2539, "lat": -16.6786 },
  "weather": [
    { "id": 800, "main": "Clear", "description": "clear sky", "icon": "01n" }
  ],
  "base": "stations",
  "main": {
    "temp": 294.98,
    "feels_like": 294.68,
    "temp_min": 294.98,
    "temp_max": 294.98,
    "pressure": 1020,
    "humidity": 56
  },
  "visibility": 10000,
  "wind": { "speed": 2.57, "deg": 190 },
  "clouds": { "all": 0 },
  "dt": 1622768950,
  "sys": {
    "type": 1,
    "id": 8372,
    "country": "BR",
    "sunrise": 1622713195,
    "sunset": 1622753450
  },
  "timezone": -10800,
  "id": 3462377,
  "name": "Goiânia",
  "cod": 200
}
*/

struct json_object* get_open_weather_response(char* city);


#endif
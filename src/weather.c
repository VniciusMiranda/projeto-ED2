#include "weather.h"

Weather_t* get_wether(struct json_object* json) {
    if(!json) return NULL;

    Weather_t* new_weather = (Weather_t*) malloc(sizeof(Weather_t));
    if(!new_weather) return NULL;

    // get main and description
    struct json_object* weather_arr, *weather, *w_main, *description;

    json_object_object_get_ex(json, "weather", &weather_arr);

    weather = json_object_array_get_idx(weather_arr, 0);

    json_object_object_get_ex(weather, "main", &w_main);
    json_object_object_get_ex(weather, "description", &description);

    strcpy(new_weather->main, json_object_get_string(w_main));

    sprintf(LOG,"weather main: %s", new_weather->main);
    log_info(LOG);
    strcpy(new_weather->description, json_object_get_string(description));

    // get temperature
    struct json_object* main, *temperature;

    json_object_object_get_ex(json, "main", &main);
    json_object_object_get_ex(main, "temp", &temperature);

    new_weather->temperature = convert_kelvin_to_celsius(json_object_get_double(temperature));

    return new_weather;
}

int update_weather(Weather_t* weather, char* city) {
    if(!weather || !city) return ERR;

    struct json_object* json = get_open_weather_response(city);
    if(!json) {
        log_error("error while updating weather");
        return ERR;
    }
    Weather_t* new_weather = get_wether(json);

    copy_weather(weather, new_weather);
    destroy_weather(new_weather);

    return OK;
}

int copy_weather(Weather_t* dest, Weather_t* src) {
    if(!dest || !src) return ERR;

    strcpy(dest->main, src->main);
    strcpy(dest->description, src->description);

    dest->temperature = src->temperature;
    return OK;
}

int print_weather(FILE* f, Weather_t* weather) {
    print_line(f, 80, '~');
    fprintf(f, "CONDICAO DO TEMPO\n");
    fprintf(f, "%s, %s\n", weather->main, weather->description);
    fprintf(f, "temperatura: %.2f\n", weather->temperature);
}

int destroy_weather(Weather_t* wc) {
    if(!wc) return ERR;
    free(wc);
}
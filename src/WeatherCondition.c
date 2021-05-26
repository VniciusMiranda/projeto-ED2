#include "WeatherCondition.h"

WeatherCondition_t filterWeatherCondition(char* content) {
    return 0;
}

void print_str_hm(char* key, void* value_ptr) {
    char* value = (char*) value_ptr;
    printf("%s -> %s\n", key, value);
}

WeatherCondition_t getWetherCondition(char* city_name) {
    if(!city_name) return ERR;

    url_params_t params = create_hm(4);
    insert_pair_hm((hash_map_t*)params, "q", city_name);
    insert_pair_hm((hash_map_t*)params, "appid", API_KEY);
    print_hm(params, print_str_hm);

    content_t content;
    content.length = 0;
    content.str = NULL;

    GETrequest(params, API_URL, &content); 
    log_info(content.str);

    return filterWeatherCondition(content.str);
}

int getName_wc(WeatherCondition_t wc, char* dest) {
    if(is_null_ptr(dest)) return ERR;

    switch(wc) {
        case SUNNY:
            getName(SUNNY, dest);
            break;
        case NOT_FOUND:
            getName(NOT_FOUND, dest);
            break;
        case CALM:
            getName(CALM, dest);
            break;
        case FOGGY:
            getName(FOGGY, dest);
            break;
        case WINDY: 
            getName(RAINY, dest);
            break;
        case STORMY:
            getName(STORMY, dest);
            break;
        default:
            strcpy(dest, "error");
    }
    return OK;
}
     

int destroyWeatherCondition(WeatherCondition_t* wc) {
    if(!wc) return ERR;
    free(wc);
}
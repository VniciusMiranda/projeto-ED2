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
            strcpy(dest, "Sunny");
            break;
        case NOT_FOUND:
            strcpy(dest, "not found");
            break;
        case CALM:
            strcpy(dest, "Calm");
            break;
        case FOGGY:
            strcpy(dest, "Foggy");
            break;
        case WINDY: 
            strcpy(dest, "Rainy");
            break;
        case STORMY:
            strcpy(dest, "Stormy");
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
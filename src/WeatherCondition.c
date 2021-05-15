#include "WeatherCondition.h"

void print_str_hm(char* key, void* value_ptr) {
    char* value = (char*) value_ptr;
    printf("%s -> %s\n", key, value);
}

WeatherCondition_t* getWetherCondition(char* city_name) {
    if(!city_name) return NULL;
    char* response_str = (char*) malloc(TEXT_MAX*sizeof(char));

    url_params_t params = create_hm(4);
    insert_pair_hm((hash_map_t*)params, "q", "london");
    insert_pair_hm((hash_map_t*)params, "appid", API_KEY);
    print_hm(params, print_str_hm);

    GETrequest(params, API_URL, &response_str); 
    log_info(response_str);

    return NULL;
}
     

int destroyWeatherCondition(WeatherCondition_t* wc) {
    if(!wc) return ERR;

    
}
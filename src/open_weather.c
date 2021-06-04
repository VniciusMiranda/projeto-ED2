#include "open_weather.h"

struct json_object* get_open_weather_response(char* city) {
    log_info("get_open_weather_response(): init");

    url_params_t params = create_hm(4);
    insert_pair_hm((hash_map_t*)params, "q", city);
    insert_pair_hm((hash_map_t*)params, "appid", API_KEY);

    content_t content;
    content.length = 0;
    content.str = NULL;

    GETrequest(params, API_URL, &content); 
    sprintf(LOG, "content: %s", content.str);
    log_info(LOG);

    log_info("parsing response to json object");

    struct json_object* json = json_tokener_parse(content.str), *cod;
    json_object_object_get_ex(json, "cod", &cod);

    int status_code = json_object_get_int(cod);

    if(status_code != 200) {
        sprintf(LOG, "request didn't return status code 200. Returned status code: %d", status_code);
        log_warning(LOG);
        return NULL;
    }

    log_info("request returned status code 200");
    return json;
}
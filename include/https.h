#ifndef _HTTPS_H_
#define _HTTPS_H_

#include <curl/curl.h>

#include "hash_map.h"
#include "utils.h"

typedef hash_map_t* url_params_t;

typedef enum method { GET, POST, PUT, DELETE } method_t;

int GETrequest(url_params_t params, char* url, char** response_str);

#endif
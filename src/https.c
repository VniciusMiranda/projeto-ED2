#include "https.h"

void _buildUrlParams(char* key, void* value_ptr, int index, void* url_ptr) {
    char** url = (char**) url_ptr;
    *url = realloc(*url, (size_t*)(TEXT_MAX + 1));
    if(is_null_ptr(*url)) exit(EXIT_FAILURE);
    char* value = (char*) value_ptr;
    index == 0 ? strcat(*url, "?") : strcat(*url, "&"); 
    strcat(*url, key);
    strcat(*url, "=");
    strcat(*url, value);
    printf("%s\n", *url);
    
    log_warning("ei");
}

size_t writefunction(void *ptr, size_t size, size_t nmemb, void* s) {
    char** str = (char**) s;
    size_t new_len = TEXT_MAX + size*nmemb;
    *str = realloc(*str, new_len+1);
    if(is_null_ptr(*str)) exit(EXIT_FAILURE);
    strcpy(*str, (char*) ptr);
    return size*nmemb;
}


int GETrequest(url_params_t params, char* url, char** response_str) {
    CURL* curl;
    CURLcode res;

    curl = curl_easy_init();
    if(!curl) return ERR;

    if(params)
        foreach_hm(params, _buildUrlParams, &url);

    curl_easy_setopt(curl, CURLOPT_URL, url);    

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_str);
      
    curl_easy_setopt(curl, CURLOPT_ALTSVC , (long) CURL_HTTP_VERSION_3);

    /* Check for errors */
    if(curl_easy_perform(curl) != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));

    curl_easy_cleanup(curl);

    return OK;
}





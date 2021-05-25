#include "https.h"


void _buildUrlParams(char* key, void* value_ptr, int index, void* url_ptr) {
    char url[TEXT_MAX];
    strcpy(url, (char*) url_ptr);
    if(is_null_ptr(url)) exit(EXIT_FAILURE);

    char* value = (char*) value_ptr;
    index == 0 ? strcat(url, "?") : strcat(url, "&"); 
    strcat(url, key);
    strcat(url, "=");
    strcat(url, value);
    printf("%s\n", url);

    strcpy((char*) url_ptr, url); 
}


size_t writecallback(char *content, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    content_t* mem = (content_t*) userp; 
    char* ptr = realloc(mem->str, mem->length + realsize + 1);
    if(is_null_ptr(ptr)) return 0;

    mem-> str = ptr;
    memcpy(&mem->str[mem->length], content, realsize);
    mem->length += realsize;
    mem->str[mem->length] = '\0';

    return size*nmemb;
}

// TODO: come back latter and make it work
int GETrequest(url_params_t params, char* _url, content_t* response) {
    CURL* curl;
    CURLcode res;
    char url[TEXT_MAX];
    strcpy(url, _url);

    curl = curl_easy_init();
    if(!curl) return ERR;

    if(params)
        foreach_hm(params, _buildUrlParams, &url);

    log_warning("url:"); 
    log_info(url);

    curl_easy_setopt(curl, CURLOPT_URL, url);    
    
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writecallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

    log_warning(response->str);
      
    curl_easy_setopt(curl, CURLOPT_ALTSVC , (long) CURL_HTTP_VERSION_3);

    /* Check for errors */
    if(curl_easy_perform(curl) != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));

    curl_easy_cleanup(curl);

    return OK;
}





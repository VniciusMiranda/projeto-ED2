#include "log.h"


int init_log() {
    if(equals(LOG_FILE_NAME, "")) {
        CUSTOM_LOG_FILE = false;
        LOG_FILE = stdout;
    }
    else {
        CUSTOM_LOG_FILE = true;
        LOG_FILE = fopen(LOG_FILE_NAME, "w");
        if(is_null_ptr(LOG_FILE)) {
            fprintf(stderr, "error when initializing application log system...\n");
            exit(EXIT_FAILURE); 
        }
    }

    log_info("application log initialized");
    return OK;
}

int set_log_file(char* file_name) {
    strcpy(LOG_FILE_NAME, file_name);
    return OK;
}

void clean_log() {
    if(CUSTOM_LOG_FILE)
        fclose(LOG_FILE);
}

int log_info(char* str) {
    char timestamp[TEXT_MAX]; 
    get_curr_asc_time(timestamp);

    fprintf(LOG_FILE,"\033[0;32m"); //Set the text to the color blue.
    fprintf(LOG_FILE, "INFO(%s): %s", timestamp, str);
    fprintf(LOG_FILE,"\033[0m"); 
    fprintf(LOG_FILE, "\n");
    
    if(CUSTOM_LOG_FILE)
        fflush(LOG_FILE);
    return OK;
}

int log_error(char* str) {
    char timestamp[TEXT_MAX]; 
    get_curr_asc_time(timestamp);

    fprintf(LOG_FILE,"\033[0;31m"); //Set the text to the color red.
    fprintf(LOG_FILE, "ERROR(%s): %s", timestamp, str);
    fprintf(LOG_FILE,"\033[0m");
    fprintf(LOG_FILE, "\n");

    if(CUSTOM_LOG_FILE)
        fflush(LOG_FILE);

    return OK;
}

int log_warning( char* str) {
    char timestamp[TEXT_MAX]; 
    get_curr_asc_time(timestamp);
  
    fprintf(LOG_FILE,"\033[0;33m"); //Set the text to the color yellow.
    fprintf(LOG_FILE, "WARN(%s): %s", timestamp, str);
    fprintf(LOG_FILE,"\033[0m"); 
    fprintf(LOG_FILE, "\n");

    if(CUSTOM_LOG_FILE)
        fflush(LOG_FILE);

    return OK;
}

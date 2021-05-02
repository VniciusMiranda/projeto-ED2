#include "log.h"


int init_log() {
    // log file diferent from stdout not suported yet
    if(equals(log_file_name, "")) {
        log_file = stdout;
        log_info("application log initialized");
        return OK;
    }

    log_error( "custom log file not suported.");
    return ERR;
}

int log_info(char* str) {
    char timestamp[TEXT_MAX]; 
    get_curr_asc_time(timestamp);

    fprintf(log_file,"\033[0;32m"); //Set the text to the color blue.
    fprintf(log_file, "INFO(%s): %s", timestamp, str);
    fprintf(log_file,"\033[0m"); 
    fprintf(log_file, "\n");

    return OK;
}

int log_error(char* str) {
    char timestamp[TEXT_MAX]; 
    get_curr_asc_time(timestamp);

    fprintf(log_file,"\033[0;31m"); //Set the text to the color red.
    fprintf(log_file, "ERROR(%s): %s", timestamp, str);
    fprintf(log_file,"\033[0m");
    fprintf(log_file, "\n");

    return OK;
}

int log_warning( char* str) {
    char timestamp[TEXT_MAX]; 
    get_curr_asc_time(timestamp);
  
    fprintf(log_file,"\033[0;33m"); //Set the text to the color yellow.
    fprintf(log_file, "WARN(%s): %s", timestamp, str);
    fprintf(log_file,"\033[0m"); 
    fprintf(log_file, "\n");

    return OK;
}

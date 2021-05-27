#include "log.h"


int init_log(bool enable_color, bool use_log_file) {
    ENABLE_COLOR = enable_color;

    if(!use_log_file) {
        CUSTOM_LOG_FILE = false;
        LOG_FILE = stdout;
    }
    else {
        CUSTOM_LOG_FILE = true;
        set_log_file("airline-management.log");
        LOG_FILE = fopen(LOG_FILE_NAME, "w");
        if(is_null_ptr(LOG_FILE)) {
            fprintf(stderr, "error when initializing application log system...\n");
            exit(EXIT_FAILURE); 
        }
    }
    log_title("APPLICATION LOG INITIALIZED", 28, '#');
    return OK;
}

int set_log_file(char* file_name) {
    strcpy(LOG_FILE_NAME, file_name);
    return OK;
}

// don't know wtf is this
void clean_log() {
    if(CUSTOM_LOG_FILE)
        fclose(LOG_FILE);
}

int log_info(char* str) {
    char timestamp[TEXT_MAX]; 
    get_curr_asc_time(timestamp);

    ENABLE_COLOR ? set_color(LOG_FILE, GREEN, false) : NULL;

    fprintf(LOG_FILE, "INFO(%s): %s", timestamp, str);

    ENABLE_COLOR ? reset_color(LOG_FILE) : NULL;

    fprintf(LOG_FILE, "\n");
    
    if(CUSTOM_LOG_FILE)
        fflush(LOG_FILE);
    return OK;
}

int log_error(char* str) {
    char timestamp[TEXT_MAX]; 
    get_curr_asc_time(timestamp);

    ENABLE_COLOR ? set_color(LOG_FILE, RED, false) : NULL;

    fprintf(LOG_FILE, "ERROR(%s): %s", timestamp, str);

    ENABLE_COLOR ? reset_color(LOG_FILE) : NULL;
    fprintf(LOG_FILE, "\n");

    if(CUSTOM_LOG_FILE)
        fflush(LOG_FILE);
    return OK;
}

int log_warning( char* str) {
    char timestamp[TEXT_MAX]; 
    get_curr_asc_time(timestamp);
  
    ENABLE_COLOR ? set_color(LOG_FILE, YELLOW, false) : NULL;

    fprintf(LOG_FILE, "WARN(%s): %s", timestamp, str);

    ENABLE_COLOR ? reset_color(LOG_FILE) : NULL; 

    fprintf(LOG_FILE, "\n");

    if(CUSTOM_LOG_FILE)
        fflush(LOG_FILE);
    return OK;
}

int log_print_line(int size, char c) {
    ENABLE_COLOR ? set_color(LOG_FILE, BLUE, true) : NULL;

    print_line(LOG_FILE, size, c);

    ENABLE_COLOR ? reset_color(LOG_FILE) : NULL; 
}

int log_title(char* str, int length, char c) {
    log_print_line(100, '#');
    int counter = 50 - length/2; 
    while(counter--) fprintf(LOG_FILE, " ");

    ENABLE_COLOR ? set_color(LOG_FILE, BLUE, true) : NULL;

    fprintf(LOG_FILE,"%s\n", str); 

    ENABLE_COLOR ? reset_color(LOG_FILE): NULL;

    log_print_line(100, '#');
}
     

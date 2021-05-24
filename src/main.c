#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h> 
#include <curl/curl.h>

#include "utils.h"
#include "log.h"

#include "Database.h"
#include "idresolver.h"
#include "options.h"

int init();

int main(int numb_args, char* args[]) {
    if(init() == ERR) {
        log_error("couldn't init application");
        exit(EXIT_FAILURE);
    }

    if(handle_options(numb_args, args) == ERR) {
        log_error( "invalid arguments...");
        log_error("exiting.");
        
        print_options();
        exit(EXIT_FAILURE);
    }

    log_error("exit success.");
    clean_log();
    exit(EXIT_SUCCESS);
}

int init() {

    curl_global_init(CURL_GLOBAL_ALL);
    init_log(true, false);
    init_database();
    resolve_table_ids();
}




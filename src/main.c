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
int clean();

int main(int numb_args, char* args[]) {
    // command line file to print on
    FILE* f = stdout;

    if(init() == ERR) {
        log_error("couldn't init application");
        exit(EXIT_FAILURE);
    }

    if(handle_options(f, numb_args, args) == ERR) {
        log_error( "invalid arguments...");
        log_error("exiting.");
        
        print_options(f);
        exit(EXIT_FAILURE);
    }

    log_info("executing clean function...");

    error_in(clean()) ? 
        log_error("main(): error while running clean.") :
        log_info("function clean didn't return errors.");

    log_info("exit application.");
    exit(EXIT_SUCCESS);
}

int init() {

    if(error_in(curl_global_init(CURL_GLOBAL_ALL))) {
        log_error("init(): error while initing curl");
        return ERR;
    }

    if(error_in(init_log(false, true))) {
        log_error("init(): error while initing log.");
        return ERR;
    }

    if(error_in(init_database())) {
        log_error("init(): error while initing database.");
        return ERR;
    }

    if(error_in(resolve_table_ids())) {
        log_error("init(): error while resolving table ids.");
        return ERR;
    }

    return OK;
}

int clean() {
}




 
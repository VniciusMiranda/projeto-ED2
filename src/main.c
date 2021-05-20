#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h> 
#include <curl/curl.h>

#include "utils.h"
#include "log.h"

#include "linked_list.h"
#include "hash_map.h"
#include "Airport.h"

#include "Database.h"
#include "idresolver.h"

char* options[] = {"run-ui", "run-cl"};
int NUMB_OPTIONS = ARRAY_SIZE(options);

int handle_options(int numb_opts, char* opts[]);
void print_options(); 

void runUi(); 
void runCl(); 

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


void print_options() {
    set_color(LOG_FILE, PURPLE, true);
    fprintf(LOG_FILE, "tente novamente passando uma das opcoes listadas:\n");
    for (int i = 0; i < NUMB_OPTIONS; i++) 
        fprintf(LOG_FILE, "\t%s\n", options[i]);
    reset_color(LOG_FILE);
}

int handle_options(int numb_opts, char* opts[]) {
    if (numb_opts != 2) return ERR; // only one argument is accepted
    if (!str_array_contains(opts[1], options, NUMB_OPTIONS)) return ERR;

    char* option = opts[1];
    equals(option, "run-ui") ? runUi() : runCl();
}

void runUi() {
    log_warning("A interface grafica nao foi implementada ainda");
}

void runCl() {
    log_warning("A interface de linha de comando nao foi implementada ainda");
}

int init() {
    set_log_file("");

    curl_global_init(CURL_GLOBAL_ALL);
    init_log();
    init_database();
    resolve_table_ids();
}




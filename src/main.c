#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h> 

#include "utils.h"
#include "log.h"

#include "linked_list.h"
#include "hash_map.h"
#include "Airport.h"

#include "Database.h"

char* options[] = {"run-ui", "run-cl"};
int NUMB_OPTIONS = ARRAY_SIZE(options);

int handle_options(int numb_opts, char* opts[]);
void print_options(); 

void runUi(); 
void runCl(); 

int init();

int main(int numb_args, char* args[]) {
    strcpy(log_file_name, "");
    init();


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
    exit(EXIT_SUCCESS);
}


void print_options() {
    fprintf(log_file, "tente novamente passando uma das opcoes listadas:\n");
    for (int i = 0; i < NUMB_OPTIONS; i++) fprintf(log_file, "\t%s\n", options[i]);
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
    init_log();
    init_db();
}




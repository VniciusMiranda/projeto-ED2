#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h> 
#include <utils.h>

// TODO: once the hashmap is implemented, refactor the options handling to use a hashmap 
char* options[] = {"run-ui", "run-cl"};
int NUMB_OPTIONS = sizeof(options)/sizeof(char*);

int handle_options(int numb_opts, char* opts[]);
void print_options(FILE* out_f); 

void runUi(); 
void runCl(); 

int main(int numb_args, char* args[]) {
 
    if(handle_options(numb_args, args) == ERR) {
        fprintf(stderr, "invalid argument.\nexiting...\n");
        print_options(stderr);
        exit(EXIT_FAILURE);
    }

    printf("exiting application... bye\n");
    exit(EXIT_SUCCESS);
}


void print_options(FILE* out_f) {
    fprintf(out_f, "valid options:\n");
    for (int i = 0; i < NUMB_OPTIONS; i++) fprintf(out_f, "\t%s\n", options[i]);
}

int handle_options(int numb_opts, char* opts[]) {
    if (numb_opts != 2) return ERR; // only one argument is accepted
    if (!str_array_contains(opts[1], options, NUMB_OPTIONS)) return ERR;

    char* option = opts[1];
    equals(option, "run-ui") ? runUi() : runCl();
}

void runUi() {
    printf("The user interface is not implemented yet :c\n");
    exit(EXIT_FAILURE);
}

void runCl() {
    printf("the command line is not implemented yet :c\n");
    exit(EXIT_FAILURE);
}




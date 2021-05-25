#include "options.h"

char* options[] = {"run-ui", "run-cl"};
int NUMB_OPTIONS = ARRAY_SIZE(options);



void print_options() {
    set_color(stdout, PURPLE, true);
    fprintf(stdout, "tente novamente passando uma das opcoes listadas:\n");
    for (int i = 0; i < NUMB_OPTIONS; i++) 
        fprintf(stdout, "\t%s\n", options[i]);
    reset_color(stdout);
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
    run_command_line(stdout);
}




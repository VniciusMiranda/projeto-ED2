#include "options.h"

char* options[] = {"run-ui", "run-cl"};
int NUMB_OPTIONS = ARRAY_SIZE(options);



void print_options(FILE* f) {
    set_color(f, PURPLE, true);
    fprintf(f, "tente novamente passando uma das opcoes listadas:\n");
    for (int i = 0; i < NUMB_OPTIONS; i++) 
        fprintf(f, "\t%s\n", options[i]);
    reset_color(f);
}

int handle_options(FILE* f, int numb_opts, char* opts[]) {
    if (numb_opts != 2) return ERR; // only one argument is accepted
    if (!str_array_contains(opts[1], options, NUMB_OPTIONS)) return ERR;

    char* option = opts[1];
    equals(option, "run-ui") ? runUi(f) : runCl(f);
}


void runUi(FILE* f) {
    print_error(f, "Inteface grafica nao implementada");
    log_error("A interface grafica nao foi implementada ainda");
}

void runCl(FILE* f) {
    run_command_line(f);
}




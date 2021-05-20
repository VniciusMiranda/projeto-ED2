#include "colors.h"

void set_color(FILE* f, color_t c, bool is_bold) {
    fprintf(f,"\033[%d;3%dm",(int) is_bold,(int) c);
}

void reset_color(FILE* f) {
    fprintf(f, "\033[0m");
}


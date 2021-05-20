#ifndef _COLORS_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum color {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    PURPLE,
    CYAN,
    WHITE,
} color_t;

void set_color(FILE* f,color_t c, bool is_bold);

void reset_color(FILE* f);

#endif
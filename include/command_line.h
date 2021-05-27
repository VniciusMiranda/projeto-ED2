#ifndef _COMMAND_LINE_H_
#define _COMMAND_LINE_H_

#include "utils.h"
#include "airport_menu.h"
#include "plane_menu.h"
typedef enum main_menu_option {
    AIRPORT_MENU = 1, 
    PLANES_MENU, 
    EXIT_APP,
} main_menu_option_t;

int run_command_line(FILE* f);

#endif






#ifndef _OPTIONS_H_
#define _OPTIONS_H_

#include "log.h"
#include "utils.h"
#include "command_line.h"


void runUi(); 
void runCl(); 

int handle_options(int numb_opts, char* opts[]);
void print_options(); 


#endif
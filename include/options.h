#ifndef _OPTIONS_H_
#define _OPTIONS_H_

#include "log.h"
#include "utils.h"
#include "command_line.h"


void runUi(FILE* f); 
void runCl(FILE* f); 

int handle_options(FILE* f, int numb_opts, char* opts[]);
void print_options(FILE* f ); 


#endif
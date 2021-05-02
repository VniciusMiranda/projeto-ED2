#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "utils.h"

#define LOG_MAX 10000

static char log_file_name[TEXT_MAX];
static FILE* log_file;

int init_log();

int log_info(char* str); 
int log_error(char* str); 
int log_warning(char* str); 

#endif
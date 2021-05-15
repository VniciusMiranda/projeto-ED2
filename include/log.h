#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "utils.h"

#define LOG_MAX 10000

static char LOG_FILE_NAME[TEXT_MAX];
bool CUSTOM_LOG_FILE;
FILE* LOG_FILE;

int init_log();
void clean_log();

int set_log_file(char* file_name);
int log_info(char* str); 
int log_error(char* str); 
int log_warning(char* str); 

#endif
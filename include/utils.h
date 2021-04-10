/* created by: Vinicius Miranda  25/03/2021 */
#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>

#include <sys/stat.h>

#include <ncurses.h>


// macros
#define getName(var, str) sprintf(str, "%s", #var) 

bool equals(const char* str1, const char *str2);

bool str_array_contains(const char* str, char* str_array[], int array_size);

bool file_exists(char *filename);

bool dir_exists(char *dir_name);

int set_last_char(char* str, char c, int size);

int substr_index(char* str, char* sub_str);

int replace_str(char* str, char* sub_str, char* rp_str);

#endif

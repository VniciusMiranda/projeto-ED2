/* created by: Vinicius Miranda  25/03/2021 */
#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>

#include <string.h>

// macros
#define getName(var, str) sprintf(str, "%s", #var) 

bool equals(const char* str1, const char *str2);

bool str_array_contains(const char* str, char* str_array[], int array_size);

#endif

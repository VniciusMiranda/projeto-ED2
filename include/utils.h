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
#include <time.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <ncurses.h>

#include "type.h"
#include "colors.h"

#define TEXT_MAX 256
typedef struct int_array {
    long int* array;
    int size;
} int_array_t;


/* get the name of a variable */
#define getName(var, str) sprintf(str, "%s", #var) 

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

bool equals(const char* str1, const char *str2);

bool str_array_contains(const char* str, char* str_array[], int array_size);

bool file_exists(char *filename);

bool dir_exists(char *dir_name);

int create_file(char* path);

int set_last_char(char* str, char c, int size);

int substr_index(char* str, char* sub_str);

int replace_str(char* str, char* sub_str, char* rp_str);

void print_line(FILE* f, int size, char c);
void print_line_with_color(FILE* f, int size, char c, color_t color, bool is_bold);

int get_curr_asc_time(char* dest);

void swap_ptr(void** a, void** b);

bool is_null_ptr(void* ptr);

bool is_not_null_ptr(void* ptr);

int print_menu_options(FILE* f, color_t color, char* options[], int size);

int get_selected_option(FILE* f, color_t color, char* options[], int size);

int print_title(FILE* f, color_t color, char* title, char line_char, int title_size);

int print_error(FILE* f, char* message);

int print_success(FILE* f, char* message);

int print_warning(FILE* f, char* message);

int clear_input_buffer();

void trim_trailing_empty_space(char* str);

bool error_in(int status);

int print_int_array(FILE* f, int_array_t a);

void long_int_to_str(long int i, char* dest);

void id_array_to_long_int_arr(char* arr, int size, long int dest[]);

int get_first_letter_upper_case_int_repr(char* str);

#endif

/* created by: Vinicius Miranda  25/03/2021 */
#include <utils.h>


bool equals(const char* str1, const char *str2) {
    return !strcmp(str1, str2);
}

bool str_array_contains(const char* str,char* str_array[], int array_size) {
    for(int i = 0; i < array_size; i++) {
        if(equals(str, str_array[i]))
            return true;
    }

    return false;    
}

bool file_exists(char *filename) {
  struct stat  buffer;   
  return (stat (filename, &buffer) == 0);
}

int set_last_char(char* str, char c, int size) {
    if(!str || !c) return ERR;
    if(strlen(str) >= size) return ERR;

    str[strlen(str)] = c;
}

bool dir_exists(char *dir_name);

int substr_index(char* str, char* sub_str) {
    int str_len = strlen(str), sub_str_len = strlen(sub_str);
    if(str_len < sub_str_len) return ERR;

    int begining = -1;
    for(int i = 0; i < str_len && str_len + i <= sub_str_len; i++) {
        if(equals(&str[i], sub_str)) begining = i; 
    }

    return begining;
}

int replace_str(char* str, char* sub_str, char* rp_str) {
    if(!str || !sub_str || !rp_str) return ERR;

    int str_len = strlen(str), sub_str_len = strlen(sub_str);
    if(str_len < sub_str_len) return ERR;

    int begining = substr_index(str, sub_str);
    if(begining == ERR) return ERR;
    if(sub_str_len > strlen(&str[begining])) return ERR;

    for(int i = 0; i < sub_str_len + 1; i++) {
        str[begining + i] = sub_str[i];
    }
}
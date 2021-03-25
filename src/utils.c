#include <utils.h>
#include <stdio.h>


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


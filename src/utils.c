/* created by: Vinicius Miranda  25/03/2021 */
#include <utils.h>


// returns true if both strings passed are equal, false otherwise 
bool equals(const char* str1, const char *str2) {
    return !strcmp(str1, str2);
}

int p_log(FILE* f, char* str, int status) {
    time_t ltime; /* calendar time */
    ltime=time(NULL); /* get current cal time */
    char* timestamp = asctime(localtime(&ltime));
    timestamp[strlen(timestamp) - 1] = '\0';
    switch (status) {
    case LOG_ERROR:
        fprintf(f,"\033[0;31m"); //Set the text to the color red.
        fprintf(f, "ERROR(%s): %s", timestamp, str);
        fprintf(f,"\033[0m"); 
        break;
     case LOG_WARNING:
        fprintf(f,"\033[0;33m"); //Set the text to the color yellow.
        fprintf(f, "WARN(%s): %s", timestamp, str);
        fprintf(f,"\033[0m"); 
        break;
     case LOG_INFO:
        fprintf(f,"\033[0;32m"); //Set the text to the color blue.
        fprintf(f, "INFO(%s): %s", timestamp, str);
        fprintf(f,"\033[0m"); 
        break;
    default:
        break;
    }
    fprintf(f, "\n");

    return OK;
};

// verify if a string array contains certain value
bool str_array_contains(const char* str,char* str_array[], int array_size) {
    for(int i = 0; i < array_size; i++) {
        if(equals(str, str_array[i]))
            return true;
    }

    return false;    
}

bool file_exists(char *filename) {
  struct stat buffer;   
  return (stat (filename, &buffer) == 0);
}

int set_last_char(char* str, char c, int size) {
    if(!str || !c) return ERR;
    if(strlen(str) >= size) return ERR;

    str[strlen(str)] = c;
    return OK;
}

bool dir_exists(char *dir_name) {
    struct stat sb;
    return stat(dir_name, &sb) == 0 && S_ISDIR(sb.st_mode); 
}

int substr_index(char* str, char* sub_str) {
    int str_len = strlen(str), substrLen = strlen(sub_str);
    if(str_len < substrLen) return ERR;

    int begining = -1;
    for(int i = 0; i < str_len; i++) {
        if(equals(&str[i], sub_str)) begining = i; 
    }

    return begining;
}

int create_file(char* path) {
    fclose(fopen(path, "w"));
}

// replace from the sub_str found in str for rp_str 
int replace_str(char* str, char* sub_str, char* rp_str) {
    if(!str || !sub_str || !rp_str) return ERR;

    int str_len = strlen(str), substrLen = strlen(sub_str); 
    int rpstrLen = strlen(rp_str);

    int begining = substr_index(str, sub_str);
    if(begining == ERR) return ERR;

    // case where the wanted operation is to erase the sub string
    // current implementation only works for the case where the 
    // substr is at the end
    if (equals(rp_str, "")) {

        for(int i = 0; i < substrLen; i++)
            str[begining + i] = (char) 0;
        return OK;
    } 

    if (substrLen == rpstrLen) {
        for(int i = 0; i < substrLen + 1; i++)
            str[begining + i] = rp_str[i];
    } 
    else if (substrLen < rpstrLen) {
        for(int i = 0; i < rpstrLen; i++) {
            if(i <= substrLen)
                str[begining + i] = rp_str[i];
            else {
                str[begining + i + 1] = str[begining + i]; 
                str[begining + i] = rp_str[i];
            } 
        }
    }
    else if (substrLen > rpstrLen) {
        for(int i = 0, j = 0; i < substrLen; i++) {
            if (i <= rpstrLen)
                str[begining + i] = rp_str[i];
            else {
                str[begining + i] = str[substrLen + j];
                j++;
            }
        }
    }

    return OK;
}

void print_line(int size, char c) {
    if(!size) size = 60;
    if(!c) c = '-';

    for(int i = 0; i < size; i++)
        printf("%c", c);
    printf("\n");
}
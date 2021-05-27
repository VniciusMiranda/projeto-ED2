/* created by: Vinicius Miranda  25/03/2021 */
#include <utils.h>


// returns true if both strings passed are equal, false otherwise 
bool equals(const char* str1, const char *str2) {
    return !strcmp(str1, str2);
}

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

void print_line(FILE* f, int size, char c) {
    if(!size) size = 60;
    if(!c) c = '-';
    if(!f) f = stdout;

    for(int i = 0; i < size; i++)
        fprintf(f, "%c", c);
    fprintf(f, "\n");
}

void print_line_with_color(FILE* f, int size, char c, color_t color, bool is_bold) {
    if(!size) size = 60;
    if(!c) c = '-';
    if(!f) f = stdout;
    set_color(f, color, is_bold);
    for(int i = 0; i < size; i++)
        fprintf(f, "%c", c);
    fprintf(f, "\n");
    reset_color(f);
}

int get_curr_asc_time(char* dest) {
    if(!dest) return ERR;

    time_t ltime; /* calendar time */
    ltime = time(NULL); /* get current cal time */
    char* timestamp = asctime(localtime(&ltime));
    timestamp[strlen(timestamp) - 1] = '\0';
    strcpy(dest, timestamp);

    return OK;
}

bool is_null_ptr(void* ptr) {
    return !ptr;
}

bool is_not_null_ptr(void* ptr) {
    return ptr;
}

void swap_ptr(void** a, void** b) {
    void* tmp = *a;
    *a = *b;
    *b = tmp;
}

int print_menu_options(FILE* f, color_t color, char* options[], int size) {
    set_color(stdout, WHITE, true);
    fprintf(f, "selecione a opcao desejada:\n");
    reset_color(f);

    set_color(stdout, color, true);
    for(int i = 0; i < size; i++) {
        fprintf(f, "%d - %s\n", i+1, options[i]);
    }
    reset_color(f);
}

int get_selected_option(FILE* f, color_t color, char* options[], int size) {
    int selected_option;

    while(true) {
        fprintf(f, ">");
        scanf("%d", &selected_option);

        if(selected_option > 0 && selected_option <= size) 
            break;

        set_color(f, RED, true); 
        fprintf(f, "ERRO:\n");
        fprintf(f, "opcao selecionada invalida!\n");
        fprintf(f, "tente novamente.\n");
        reset_color(f);

        set_color(f, WHITE, true);
        print_line(f, 80, '-');
        reset_color(f);

        print_menu_options(f, color, options, size);
    }

    return selected_option;
}

int print_title(FILE* f, color_t color, char* title, char line_char, int title_size) {
    int line_size = 80;

    set_color(f, color, true);
    print_line(f, line_size, line_char);
    reset_color(f);

    // centralize the text
    int center_pos = line_size/2 - title_size; 
    while(center_pos--) fprintf(f," ");

    set_color(f, WHITE, true);
    fprintf(f, "%s\n", title);
    reset_color(f);

    set_color(f, color, true);
    print_line(f, line_size, line_char);
    reset_color(f);
}

int print_error(FILE* f, char* message) {
    set_color(f, RED, true);
    fprintf(f, "ERROR:\n");
    fprintf(f, "%s\n", message);
    reset_color(f);
}

int print_success(FILE* f, char* message) {
    set_color(f, GREEN, true);
    fprintf(f, "SUCESSO:\n" );
    fprintf(f, "%s\n", message);
    reset_color(f);
}

int print_warning(FILE* f, char* message) {
    set_color(f, YELLOW, true);
    fprintf(f, "ATENÇÃO:\n");
    fprintf(f, "%s\n", message);
    reset_color(f);
}

int clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  
}

void trim_trailing_empty_space(char* str)
{
    int index, i;
    index = -1;
    i = 0;
    while(str[i] != '\0'){
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
            index= i;
        }
        i++;
    }
    str[index + 1] = '\0';
}

int print_int_array(FILE* f, int_array_t a) {
    int i = 0;
    while(true) {
        fprintf(f, "%ld", a.array[i]);
        if(i >= a.size) break; 
        i++;
    }
    fprintf(f,"\n");
}

bool error_in(int status) {
    return status == ERR;
}


 /*
    the use of connections are related to features that will be implemented
    on the major version 2.0.0
*/

// int get__id_array_size(id_array_t arr) {
//     char* str = (char*) arr;  
//     int i = 0, size = 0;
    
//     while(str[i]) {
//         if(str[i] == ',')
//             size++;
//     }

//     return size - 2;
// }

// the sizes of @arr and @dest must be equal
// void id_array_to_long_int_arr(char* arr, int size, long int dest[]) {
//     int id, id_size;
//     int first_idx = -1, second_idx = -1;

//     for(int j = 0,i = 0; i < size; i++) {
//         if(first_idx != -1 && second_idx != -1) {
//             dest[j++] = (long int) strtol(arr + first_idx, arr + second_idx, 10);

//             // reset indexes 
//             first_idx = -1;
//             second_idx = -1;
//         }

//         if(arr[i] == ',')
//             first_idx = i + 1;

//         if(first_idx != -1 && arr[i] == ',')
//             second_idx = i - 1;
//     }

// }

// void long_int_to_str(long int i, char* dest) {
//     sprintf(dest, "%ld", i);
// }

int get_first_letter_upper_case_int_repr(char* str) {
    int first_letter = (int) str[0]; 
    if(first_letter >= 97) {
        first_letter -= 32;
    }
    return first_letter;
}


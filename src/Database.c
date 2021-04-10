#include <Database.h>

int _getDefaultPath_db(char* dest, char* db_name);
int _getCustomPath_db(char* dest, char* path, char* db_name);
int _getRootPath_db(char* dest, char* path, char* db_name);


Database_t* create_db(char* name, char* path) {
    char db_path[PATH_MAX]; 
    char db_root_path[PATH_MAX];
    if(!path) 
        _getDefaultPath_db(db_path, name);
    else { 
        char _p[PATH_MAX];
        strcpy(_p, path);
        _getCustomPath_db(db_path,_p, name);
    }
    _getRootPath_db(db_root_path, db_path, name);

}


int _getCustomPath_db(char* dest, char* path, char* db_name) {
    if(!dest || !path || !db_name) return ERR;

    if(path[strlen(path) - 1] != '/') set_last_char(path, '/', PATH_MAX);
    strcat(path, DATABASE_DIR);
    strcat(path, db_name);
    strcpy(dest, path);
    
    return OK;
}

int _getDefaultPath_db(char* dest, char* db_name) {
    if(!dest || !db_name) return ERR;

    strcpy(dest, getenv("HOME"));
    set_last_char(dest, '/', PATH_MAX);
    strcat(dest, DATABASE_DIR);
    strcat(dest, db_name);

    return OK;
}

int _getRootPath_db(char* dest, char* path, char* db_name);
     
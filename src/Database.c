#include "Database.h"

/*
    creates a new database.
    params:
        name required
        path -> default value = $HOME/.DB_ED2/@name 
    
    If NULL if pass as @path the default value is use.
*/
Database_t* create_db(char* name, char* path) {
    char db_path[PATH_MAX], db_name[PATH_MAX]; 
    char log[LOG_MAX];

    strcpy(db_name, name);

    get_path_db(db_path, db_name);

    sprintf(log, "db_path: %s", db_path);
    p_log(stdout, log, LOG_INFO);

    if(db_exists(db_name)) {
        sprintf(log, "database of name %s already exists", db_name);
        p_log(stdout, log, LOG_ERROR);
        return NULL;
    } 

    sprintf(log, "allocating memory for database %s", db_name);
    p_log(stdout, log, LOG_INFO); 
    Database_t* db = (Database_t*) malloc(sizeof(Database_t)); 
    if(!db) return NULL;

    db->created = time(NULL);
    strcpy(db->name, db_name);
    for(int i = 0; i < TABLE_MAX; i++)
        db->tables[i] = NULL;

    // write_initial_info_db(db);  
    
    return db;
}

int _build_dir_db(char* db_name) {
    char log[LOG_MAX]; 
    char dir_path[PATH_MAX], info_path[PATH_MAX];
    get_path_db(dir_path, db_name);
    // get_info_file_path(info_path, db_name);
    // TODO: find cleaner way to print formated str on logs
    sprintf(log, "dir path: %s", dir_path);
    p_log(stdout, log, LOG_INFO);

    mkdir(dir_path, 0777);

    p_log(stdout, "creating configuration file", LOG_INFO);
    sprintf(log, "file path: %s", info_path);
    p_log(stdout, log, LOG_INFO);

    create_file(info_path);

    return OK;
}

bool db_exists(char* name) {
    if(!name) return false;
    char path[PATH_MAX];
    get_path_db(path, name);
    return dir_exists(path);
}

int get_info_file_path(char* dest, char* db_name){
    if(!dest || ! db_name) return ERR;

    get_path_db(dest, db_name);
    set_last_char(dest, '/', PATH_MAX);
    strcat(dest, INFO_FILE);

    return OK;
}


int get_root_dir_db(char* dest) {
    if(!dest) return ERR;

    strcpy(dest, getenv("HOME"));
    set_last_char(dest, '/', PATH_MAX);
    strcat(dest, DATABASE_DIR);

    return OK;
};


int get_path_db(char* dest, char* db_name) {
    if(!dest || !db_name) return ERR;

    // get_dir_db(dest);
    strcat(dest, db_name);

    return OK;
}
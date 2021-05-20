#include "Database.h"

char* tables[] = {
    "airport",
    "planes"
};

int NUMB_DATABASE_TABLES = ARRAY_SIZE(tables);

int init_database(FILE* f) {
    getcwd(DB_PATH, PATH_MAX);
    log_info("initializing database");

    strcat(DB_PATH, DB_DIR);

    if(!dir_exists(DB_PATH)) {
        log_warning( "database directory doesn't exists");
        log_info( "creating database dir");
        if(mkdir(DB_PATH,0777) == ERR) {
            log_error("unable to create database directory");
            exit(EXIT_FAILURE);
        }
        else {
            sprintf(LOG,"database dir created. path: %s", DB_PATH); 
            log_info(LOG);
        }
    }

    init_database_tables();
}

int init_database_tables() {
    log_info("processing tables.");
    for(int i = 0; i < NUMB_DATABASE_TABLES; i++) {
        sprintf(LOG, "[%d/%d] processing...", i + 1, NUMB_DATABASE_TABLES);
        log_info(LOG);
        create_database_table(tables[i]);
    }
    log_info( "finish processing tables");
    return OK;
}

int create_database_table(char* table_name) {
    char table_path[PATH_MAX];

    get_database_table_path(table_path, table_name);

    if(file_exists(table_path)) {
        sprintf(LOG, "table %s already exists", table_name);
        log_info(LOG);
        return OK;
    }

    sprintf(LOG, "creating storage file for %s", table_name); 
    log_info(LOG);

    if(create_file(table_path) == ERR) {
        sprintf(LOG, "unable to create %s table", table_name);
        log_error(LOG);
        exit(EXIT_FAILURE);
    }
    sprintf(LOG,"table %s created",table_name);
    log_info(LOG);
}

int get_database_table_path(char* dest, char* table_name) {
    strcpy(dest, DB_PATH);
    strcat(dest, table_name);
    strcat(dest, ".dat");

    return OK;
}

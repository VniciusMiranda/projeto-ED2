#include "Database.h"

char* tables[] = {
    "airport",
};
int NUMB_TABLES_DB = ARRAY_SIZE(tables);


int init_db(FILE* f) {
    char log[LOG_MAX];
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
            sprintf(log,"database dir created. path: %s", DB_PATH); 
            log_info( log);
        }
    }

    init_tables_db();

}

int init_tables_db() {
    char log[LOG_MAX];
    log_info("processing tables.");
    for(int i = 0; i < NUMB_TABLES_DB; i++) {
        sprintf(log, "[%d/%d] processing...", i + 1, NUMB_TABLES_DB);
        log_info(log);
        init_table_db(tables[i]);
    }
    log_info( "finish processing tables");
    return OK;
}

int init_table_db(char* table_name) {
    char log[LOG_MAX];
    char table_path[PATH_MAX];

    getTablePath_db(table_path, table_name);

    if(file_exists(table_path)) {
        sprintf(log, "table %s already exists", table_name);
        log_info(log);
        return OK;
    }

    sprintf(log, "creating storage file for %s", table_name); 
    log_info(log);

    if(create_file(table_path) == ERR) {
        sprintf(log, "unable to create %s table", table_name);
        log_error(log);
        exit(EXIT_FAILURE);
    }
    sprintf(log,"table %s created",table_name);
    log_info(log);
}

int getTablePath_db(char* dest, char* table_name) {
    strcpy(dest, DB_PATH);
    strcat(dest, table_name);
    strcat(dest, ".txt");

    return OK;
}

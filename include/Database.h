#ifndef __DATABASE_H_
#define __DATABASE_H_

#include <stdio.h>
#include <stdlib.h> 

#include <utils.h>


#define DATABASE_DIR        ".DB_ED2/"
#define STORAGE_DIR         "STORAGE/"
#define INFO_FILE           "info.dat" 

#define TABLE_MAX 100


typedef struct database {
    char* name;
    char* tables[TABLE_MAX];
    time_t created;
} Database_t;

// creates database. Default path to storage /home/@user/.DB_ED2/@dbname/STORAGE
Database_t* create_db(char* name, char* path);

// dealocates all the information related with this database
// from the current execution
int destroy_db(Database_t* db);

// deletes al the data current stored on the database
int purge_db(Database_t* db_name);

// loads data from @db_name on the program
Database_t* load_db(char* db_name);

bool db_exists(char* name);

int get_path_db(char* dest, char* db_name);
#endif
#ifndef _DATABASE_H_
#define _DATABASE_H_

#include "utils.h"
#include "log.h"

#define DB_DIR "/database/" 
#define MAX_FOREIGN_KEY 400L

static char DB_PATH[PATH_MAX];

typedef enum operation { _INSERT= 1, _DELETE,  _UPDATE, _SELECT } database_operation_t;

int init_database();

int clean_database();

int init_database_tables();

int create_database_table(char* table_name);

int delete_database_table(char* table_name);

int recreate_database_table(char* table_name);

int get_database_table_path(char* dest, char* table_name);

bool all_registers(void* d, void* cmp);

#endif
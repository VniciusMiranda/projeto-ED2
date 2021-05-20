#ifndef _DATABASE_H_
#define _DATABASE_H_

#include "utils.h"
#include "log.h"

#include "hash_map.h"

#define DB_DIR "/database/" 
#define MAX_FOREIGN_KEY 400L

static char DB_PATH[PATH_MAX];

int init_database();

int init_database_tables();

int create_database_table(char* table_name);

int get_database_table_path(char* dest, char* table_name);


#endif
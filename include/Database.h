#ifndef _DATABASE_H_
#define _DATABASE_H_

#include "utils.h"
#include "log.h"

#include "hash_map.h"

#define DB_DIR "/database/" 

static char DB_PATH[PATH_MAX];

int init_db();
int init_tables_db();
int init_table_db(char* table_name);
int getTablePath_db(char* dest, char* table_name);


#endif
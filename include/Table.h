#ifndef __TABLE_H__
#define __TABLE_H__

#include <stdio.h>
#include <stdlib.h>

#include <Database.h>
#include <Column.h>

typedef struct table {
    long int id;
    char* table_path;
    Column_t* columns[];
} Table_t;



Table_t* createTable(Database_t* db, Column_t* columns[], int size, char* name, int id); 


int destroyTable(Table_t* t);

#endif
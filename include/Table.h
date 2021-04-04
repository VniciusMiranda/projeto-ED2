/* created by: Vinicius Miranda  25/03/2021 */
#ifndef __TABLE_H__
#define __TABLE_H__

#include <stdio.h>
#include <stdlib.h>

#include <Column.h>

typedef struct table {
    long int id;
    char* file_name;
    Column_t* columns[];
} Table_t;


Table_t* createTable();

#endif
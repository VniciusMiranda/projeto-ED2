/* created by ViniciusMiranda 21/03/2021 */
#ifndef __DATABASE_H_
#define __DATABASE_H_ 1

#include <stdio.h>
/* created by: Vinicius Miranda - 25/03/2021 */
#include <stdlib.h> 
#include <Table.h>

typedef struct database {
    char* name;
    time_t created;
} Database_t;


Database_t* create();

int destroy(Database_t* db);

#endif
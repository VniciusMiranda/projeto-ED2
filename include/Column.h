/* created by: Vinicius Miranda - 25/03/2021 */
#ifndef __COLUMN_H__
#define __COLUMN_H__

typedef enum type { INT, STRING, CHAR, ARRAY_INT } type_t; 

typedef struct column {
    type_t type;
    char* content;
} Column_t;

#endif
#ifndef _TYPE_H_
#define _TYPE_H_

#include <stddef.h>
#include <stdint.h>

typedef enum type { 
    BOOL, 

    FLOAT,

    INT, 
    INT_ARRAY,
    UNSIGNED_INT,

    SHORT_INT,
    UNSIGNED_SHORT_INT,

    LONG_INT,
    LONG_LONG_INT,
    UNSIGNED_LONG_INT,
    UNSIGNED_LONG_LONG_INT,

    DOUBLE,
    LONG_DOUBLE,

    CHAR, 
    CHAR_ARRAY,
    SIGNED_CHAR,
    UNSIGNED_CHAR,

    VOID_PTR,
    INT_PTR,
    CHAR_PTR,

    OTHER
} type_t;


/* get the type of a variable */
#define typeof(x) _Generic((x),                         \
    bool: BOOL,                                         \
    unsigned char: UNSIGNED_CHAR,                       \
    char: CHAR,                                         \
    signed char: SIGNED_CHAR,                           \
    short int: SHORT_INT,                               \
    unsigned short int: UNSIGNED_SHORT_INT,             \
    int: INT,                                           \
    unsigned int: UNSIGNED_INT,                         \
    long int: LONG_INT,                                 \
    unsigned long int: UNSIGNED_LONG_INT,               \
    long long int: LONG_LONG_INT,                       \
    unsigned long long int: UNSIGNED_LONG_LONG_INT,     \
    float: FLOAT,                                       \
    double: DOUBLE,                                     \
    long double: LONG_DOUBLE,                           \
    char *: CHAR_PTR,                                   \
    void *: VOID_PTR,                                   \
    int *: INT_PTR,                                     \
    default: OTHER)                                                            


#endif


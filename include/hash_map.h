#ifndef _HASH_MAP_H_
#define _HASH_MAP_H_

#define MAP_SIZE_FACTOR 2
#define MAP_INITIAL_SIZE 50

#include "utils.h"
#include "log.h"

typedef struct pair {
    char key[TEXT_MAX];
    void* value;

    struct pair* next;
} pair_t;

typedef struct hash_map {
    int size;
    int numb_pairs;

    pair_t** pairs; 
} hash_map_t;


hash_map_t* create_hm(unsigned int size); 

int destroy_hm(hash_map_t* hm);

int hash_hm(hash_map_t* hm, char* key);

int insert_pair_hm(hash_map_t* hm, char* key, void* value);

int delete_pair_hm(hash_map_t* hm, char* key, void* value);

int foreach_hm(hash_map_t* hm,void(*func)(char*, void*, int, void*), void* d);

int print_hm(hash_map_t* hm, void(*print_func)(char*, void*));

#endif



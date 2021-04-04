/* created by: Vinicius Miranda  25/03/2021 */
#ifndef __LINK_LIST_H__
#define __LINK_LIST_H__

#include <utils.h>


typedef struct element {
    void* data;
    struct element* next;
    struct element* prev;
} element_t;

typedef struct link_list {
    int length;
    element_t* head;
} linked_list_t;


linked_list_t* create();

int destroy(linked_list_t* l);

int insert(linked_list_t* l, void* d);

int insertAt(linked_list_t* l, int index);

int getFrom(linked_list_t* l, int index);

int remove(linked_list_t* l, bool(*find_func)(void*));

void* find(linked_list_t* l, bool(*find_func)(void*));

void** findAll(linked_list_t* l, bool(*find_func)(void*));

int indexOf(linked_list_t* l, bool(*find_func)(void*));

bool contains(linked_list_t* l, bool(*find_func)(void*));

#endif




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
    element_t* tail;
} linked_list_t;


linked_list_t* create_list();

int destroy_list(linked_list_t* l);

int insert_element(linked_list_t* l, void* d);

int insert_element_at(linked_list_t* l, unsigned int index, void* d);

void* get_element_from(linked_list_t* l, int index);

int remove_element(linked_list_t* l, bool(*find_func)(void*));

int remove_element_from(linked_list_t* l,unsigned int index);

void* find_element(linked_list_t* l, bool(*find_func)(void*));

int find_all_elements(linked_list_t* l, bool(*find_func)(void*), void* result[], int* numb_results);

int index_of_element(linked_list_t* l, bool(*find_func)(void*));

bool contains_element(linked_list_t* l, bool(*find_func)(void*));

int print_list(linked_list_t* l, void(*print_func)(void*), FILE* f);

#endif




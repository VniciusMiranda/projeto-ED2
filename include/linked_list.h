#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include "utils.h"

#define DESCENDING 0
#define ASCENDING 1


typedef struct element {
    void* data;
    struct element* next;
    struct element* prev;
} element_t;

typedef struct linked_list {
    int length;
    element_t* head;
    element_t* tail;
} linked_list_t;

typedef int (*get_attr_func)(void*);

typedef bool(*search_func)(void*, void*);

/*
    Creates a generic linked list.
    params: none.
    return: linked_list_t* l => list created.
*/
linked_list_t* create_list();

/*
    Dealocates the memory of a linked list.
    params: linked_list_t* l => list to be destoy.
    return: status code.
*/
int destroy_list(linked_list_t* l, int(dealloc)(void*));

/*
    Insert element at the end of the list.
    params:
        linked_list_t* l => linked list where the element will be incerted.
        void* d => data to be stored on the list.
    return: status code.
*/
int insert_element(linked_list_t* l, void* d);

/*
    Insert element at the position "index".
    Obs: This function doesn't override the element in the current position,
    it just moves the current element to the next position.
    params:
        linked_list_t* l => linked list where the element will be incerted.
        unsigned int index => index of the position.
        void* d => data to be stored on the list.
    return: status code.
*/
int insert_element_at(linked_list_t* l, unsigned int index, void* d);

/*
    Returns the element of the position "index".
    params:
        linked_list_t* l
        unsigned int index
    return: void* => data at position "index".    
*/
void* get_element_from(linked_list_t* l,unsigned int index);

/*
    Remove element that matches the condition given by "find_func".
    params:
        linked_list_t* l
        bool(*find_func)(void*, void*) => function pointer that evaluate if 
            the element is the one to be removed.
        void* cmp => this value will be pass to "find_func" as second parameter. 
    return: status code.
*/
int remove_element(linked_list_t* l, bool(*find_func)(void*, void*), void* cmp);

/*
    Remove element from position "index".
    params:
        linked_list_t* l
        unsigned int index
    return: status code.
*/
int remove_element_from(linked_list_t* l, unsigned int index);

/*
    Returns the element that matches the condition given by "find_func".
    params:
        linked_list_t* l
        bool(*find_func)(void*, void*) => function pointer that evaluate if 
            the element is the one to be returned.
        void* cmp => this value will be pass to "find_func" as second parameter. 
    return: void* => element found.
*/
void* find_element(linked_list_t* l, bool(*find_func)(void*, void*), void* cmp);

/*
    Returns the elments that matches the condition given by "find_func".
    params:
        linked_list_t* l
        bool(*find_func)(void*, void*) => function pointer that evaluate if 
            the element is the one to be returned.
        void* cmp => this value will be pass to "find_func" as second parameter. 
    return: status code.
*/
int find_all_elements(linked_list_t* l, bool(*find_func)(void*, void*), void* result[], int* numb_results, void* cmp);

/*
    Returns the index of the element that matches the condition given by "find_func".
    params:
        linked_list_t* l
        bool(*find_func)(void*, void*) => function pointer that evaluate if 
            the element is the one to be returned.
        void* cmp => this value will be pass to "find_func" as second parameter. 
    return: index of the element found.
*/
int index_of_element(linked_list_t* l, bool(*find_func)(void*, void*), void* cmp);

/*
    Verify if containsthe element that matches the condition given by "find_func".
    params:
        linked_list_t* l
             the element is the one to be returned.
        void* cmp => this value will be pass to "find_func" as second parameter. 
        
*/
bool contains_element(linked_list_t* l, bool(*find_func)(void*, void*), void* cmp);
/*
    Prints the list.
    params:
        FILE* f 
        linked_list_t* l
        print_func => function that will print the values of the data.
    return: status code.
*/
int print_list(FILE* f, linked_list_t* l, void(*print_func)(FILE*, void*, color_t, bool), color_t color, bool is_bold);

/*
    Sort the list by the attribute of the struct returned by
    @get_attr_func function.
    params:
        linked_list_t* l
        get_attr_func
    return: status code.
*/
int sort_list(linked_list_t* l, int(*get_attr_func)(void*), int option);

/*
    Copy list @src to @dest.
    params:
        linked_list_t* dest
        linked_list_t* src
    return: status code.
*/
int copy_list(linked_list_t* dest, linked_list_t* src);


int for_each_element(linked_list_t* l, int(*process)(void*));

bool is_empty_list(linked_list_t* l);

#endif


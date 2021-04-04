#include <linked_list.h>

/*
    creates a generic link list.
    params: none
    return: linked_list_t*
*/
linked_list_t* create() {
    linked_list_t* l = (linked_list_t*) malloc(sizeof(linked_list_t)); 
    if(!l) return NULL;

    l->head = NULL;
    l->length = 0;

    return l;
}

int destroy(linked_list_t* l) {

    element_t* element = l->head, *el_memory;
    while(!element) {
        el_memory = element;
        free(el_memory);
        element = element->next;
    } 

    free(l);
    return OK;
}

int insert(linked_list_t* l, void* d) {
    if(!l || !d) return ERR;

    element_t* new_element = (element_t*) malloc(sizeof(element_t)); 
    if(!new_element) return ERR;

    new_element->data = d;

    if(!l->head) {
        new_element->prev = new_element;
        new_element->next = new_element;
        l->head = new_element;

        return OK;
    }

    element_t* head = l->head;

    new_element->next = head; 
    new_element->prev = head->prev;
    new_element->prev->next = new_element;

    head->prev = new_element;
    
    return OK;

}

int insertAt(linked_list_t* l, int index);

int getFrom(linked_list_t* l, int index);

int remove(linked_list_t* l, bool(*find_func)(void*));

void* find(linked_list_t* l, bool(*find_func)(void*));

void** findAll(linked_list_t* l, bool(*find_func)(void*));

int indexOf(linked_list_t* l, bool(*find_func)(void*));

bool contains(linked_list_t* l, bool(*find_func)(void*));
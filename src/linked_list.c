#include <linked_list.h>


linked_list_t* create_list() {
    linked_list_t* l = (linked_list_t*) malloc(sizeof(linked_list_t)); 
    if(!l) return NULL;

    l->head = NULL;
    l->tail = NULL;
    l->length = 0;

    return l;
}

int destroy_list(linked_list_t* l) {

    element_t* e = l->head, *tmp;
    while(e) {
        tmp = e;
        e = e->next;
        free(tmp);
    } 

    free(l);
    return OK;
}

int insert_element(linked_list_t* l, void* d) {
    if(!l || !d) return ERR;

    element_t* new_element = (element_t*) malloc(sizeof(element_t)); 
    if(!new_element) return ERR;

    new_element->data = d;

    if(!l->head) {
        new_element->prev = NULL;
        new_element->next = NULL;
        l->head = new_element;
        l->tail = new_element;
        l->length++;
        return OK;
    }

    element_t* head = l->head;

    new_element->next = NULL; 
    new_element->prev = l->tail;
    new_element->prev->next = new_element;
    l->tail = new_element;

    l->length++;
    
    return OK;

}

int insert_element_at(linked_list_t* l, unsigned int index, void* d) {
    if(!l || !d || index >= l->length) return ERR;

    element_t* temp;
    element_t* new_element = (element_t*) malloc(sizeof(element_t)); 
    if(!new_element) return ERR;

    if(l->length/2 < index) {
        temp = l->head;
        for(int i = 0; i < index && temp; i++) temp = temp->next;
    }
    else {
        temp = l->tail;
        for(int i = l->length; i > index && temp; i--) temp = temp->prev;
    }

    new_element->data = d;
    new_element->next = temp;

    if(temp->prev)
        temp->prev->next = new_element;

    temp->prev = new_element;

    if(temp == l->head)
        l->head = new_element;
    
    new_element->prev = temp->prev;

    return OK;
}

void* get_element_from(linked_list_t* l,unsigned int index) {
    if(!l || index >= l->length) return NULL;

    element_t* temp;
    if(l->length/2 < index) {
        temp = l->head;
        for(int i = 0; i < index && temp; i++) temp = temp->next;
    }
    else {
        temp = l->tail;
        for(int i = l->length; i > index && temp; i--) temp = temp->prev;
    }
   
    return temp->data;
}

int remove_element(linked_list_t* l, bool(*find_func)(void*, void*), void* cmp) {
    if(!l) return ERR;

    element_t* e = l->head, *tmp;
    while(e) {
        if(find_func(e->data, cmp)) {
            tmp = e;
            if(tmp == l->head)
                l->head = l->head->next;
            
            if(tmp == l->tail)
                l->tail = l->tail->prev;

            if(tmp->next != NULL)
                tmp->next->prev = tmp->prev;
            
            if(tmp->prev != NULL)
                tmp->prev->next = tmp->next;

            free(tmp);
            break; 
        }
        e = e->next; 
    }

    return ERR;
}


int remove_element_from(linked_list_t* l, unsigned int index) {
    if(!l) return ERR;
    if(l->length > index) return ERR;

    element_t* tmp;
    if(l->length/2 < index) {
        tmp = l->head;
        for(int i = 0; i < index && tmp; i++) tmp = tmp->next;
    }
    else {
        tmp = l->tail;
        for(int i = l->length; i > index && tmp; i--) tmp = tmp->prev;
    }

    if(tmp == l->head)
        l->head = l->head->next;
    
    if(tmp == l->tail)
        l->tail = l->tail->prev;

    if(tmp->next != NULL)
        tmp->next->prev = tmp->prev;
    
    if(tmp->prev != NULL)
        tmp->prev->next = tmp->next;

    free(tmp);
    return OK;
}

void* find_element(linked_list_t* l, bool(*find_func)(void*, void*), void* cmp) {
    if(!l) return NULL;

    element_t* tmp;
        tmp = l->head;
        for(int i = 0;tmp; i++) {
            if(find_func(tmp->data, cmp))
                return tmp->data;
            tmp = tmp->next;
        }
    
    return NULL;
}

int find_all_elements(linked_list_t* l, bool(*find_func)(void*, void*), void* result[], int* numb_results, void* cmp) {
    if(!l ||  !result) return ERR;

    int result_size = 0;

    element_t* tmp = l->head;
    for(int i = 0; tmp ;i++) {
        if(find_func(tmp->data, cmp))
            result[result_size++] = tmp->data;
    }
    *numb_results = result_size;

    return OK;
}

int index_of_element(linked_list_t* l, bool(*find_func)(void*, void*), void* cmp) {
    if(!l) return ERR;

    element_t* tmp = l->head;
    int i = 0;
    while(tmp) {
        if(find_func(tmp->data, cmp))
            return i;
        tmp = tmp->next;
        i++;
    }

   
    return ERR;
}

bool contains_element(linked_list_t* l, bool(*find_func)(void*, void*), void* cmp) {
    if(!l) return false;

    element_t* tmp = l->head;
    while(tmp) {
        if(find_func(tmp->data, cmp))
            return true;
        tmp = tmp->next;
    }

    return false;
}

int print_list(FILE* f, linked_list_t* l, void(*print_func)(FILE*,void*)) {
    if(!l) return ERR;
    if(!f) f = stdout;
   

    element_t* e = l->head;
    while(e) {
        print_func(f, e->data);
        e = e->next;
    }
}

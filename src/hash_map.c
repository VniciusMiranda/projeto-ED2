#include "hash_map.h"

hash_map_t* create_hm(unsigned int size) { 
    if(!size) return NULL;

    hash_map_t* new_hm = (hash_map_t*) malloc(sizeof(hash_map_t));
    if(!new_hm) return NULL;

    new_hm->numb_pairs = 0;

    new_hm->pairs = (pair_t**) malloc(sizeof(pair_t*)*size);
    if(!new_hm->pairs) return NULL;

    for(int i = 0; i < size; i++)
        new_hm->pairs[i] = NULL;

    new_hm->size = size;

    return new_hm;
}

int destroy_hm(hash_map_t* hm) {
    if(!hm) return ERR; 

    pair_t* aux = hm->pairs[0], *tmp;
    while(aux) {
        tmp = aux;
        aux = aux->next;
        free(tmp);
    }
    free(hm);

    return OK;
}

int hash_hm(hash_map_t* hm, char* key){
    if(!hm) return ERR;
    unsigned long hash = 5381;
    int c;

    while (c = *key++)
        hash = ((hash << 5) + hash) + c;

    return hash % hm->size;
}

int insert_pair_hm(hash_map_t* hm, char* key, void* value) {
    if(!hm || !value || !key) return ERR;

    int pos = hash_hm(hm, key);

    pair_t* new_p = (pair_t*) malloc(sizeof(pair_t));
    if(!new_p) return ERR;

    strcpy(new_p->key, key);
    new_p->value = value;
    new_p->next = NULL;

    if(!hm->pairs[pos]) {
        hm->pairs[pos] = new_p;
        hm->numb_pairs++;
        return OK;
    }

    pair_t* aux = hm->pairs[pos];
    while(aux->next) 
        aux = aux->next; 

    aux->next = new_p; 
    hm->numb_pairs++;
    
    return OK;
}

int delete_key_hm(hash_map_t* hm, char* key) {
    if(!hm || !key) return ERR;

    int pos = hash_hm(hm, key);

    pair_t* aux = hm->pairs[pos], *prev;

    if(equals(aux->key, key)) {
        hm->pairs[pos] = aux->next;
        free(aux);
        return OK;
    }

    while(aux) {
        if(equals(aux->key, key)) {
            prev->next = aux->next;
            free(aux);
            return OK;
        }

        prev = aux;
        aux = aux->next;
    }

    return ERR;
}

void* get_value_hm(hash_map_t* hm, char* key) {
    if(!hm || !key) return NULL;

    int pos = hash_hm(hm, key);
    if(!hm->pairs[pos]) return NULL;

    if(equals(hm->pairs[pos]->key, key))
        return hm->pairs[pos]->value;

    pair_t* aux = hm->pairs[pos];

    while(aux) {
        if(equals(aux->key, key))
            return aux->value;
        aux = aux->next;
    }

    return NULL;
} 

int foreach_hm(hash_map_t* hm,void(*func)(char*, void*, int, void*), void* d) {
    int j = 0;
    for(int i = 0; i < hm->size; i ++) {
        if(is_not_null_ptr(hm->pairs[i])) {
            pair_t* p = hm->pairs[i];
            while(p) {
                func(p->key, p->value, j, d);
                j++;
                p = p->next;
            }
        }
    }
    return OK;
}

int print_hm(hash_map_t* hm, void(*print_func)(char*, void*)) {
    for(int i = 0 ; i < hm->size; i++) {
        if(is_not_null_ptr(hm->pairs[i])) {
            pair_t* p = hm->pairs[i];
            while(p) {
                print_func(p->key,p->value);
                p = p->next;
            }
        }
    }

}







#include "sort.h"

int quick_sort(void* vec[],int size, int(*get_attr_func)(void*)) {
    if(!vec) return ERR;
}

int bubble_sort(void* vec[], int size, int(*get_attr_func)(void*)); 

int merge_sort(void* vec[], int size, int(*get_attr_func)(void*));

int heap_sort(void* vec[], int size, int(*get_atr_func)(void*));

int insertion_sort(void* vec[], int size, int(*get_attr_func)(void*));


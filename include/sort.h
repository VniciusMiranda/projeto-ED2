#ifndef _SORT_H_
#define _SORT_H_

#include "utils.h"

int quick_sort(void* vec[],int size, int(*get_attr_func)(void*));

int bubble_sort(void* vec[], int size, int(*get_attr_func)(void*)); 

int merge_sort(void* vec[], int size, int(*get_attr_func)(void*));

int heap_sort(void* vec[], int size, int(*get_atr_func)(void*));

int insertion_sort(void* vec[], int size, int(*get_attr_func)(void*));


#endif
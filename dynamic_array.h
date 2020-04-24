#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#define DYNAMIC_ARR_INC_UNIT 5

#include <stdlib.h>

typedef struct {
	void* elems;
	int current;
	int size;
	char* _typename;
	int _typesize;
} DYNAMIC_ARRAY;

void append_array_int(void* arr, int index, void* elem_addr);
void append_array_double(void* arr, int index, void* elem_addr);

void init_dynamic_array(DYNAMIC_ARRAY* arr, int elems_size);
void push_dynamic_array( DYNAMIC_ARRAY* arr, void* elem_addr,
						 void (*append_func)(void* arr, int index, void* elem_addr), int elem_size );
void pop_dynamic_array(DYNAMIC_ARRAY* arr);
void release_dynamic_array(DYNAMIC_ARRAY* arr);

#endif
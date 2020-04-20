#include "dynamic_array.h"

void append_array_int(void* arr, int index, void* elem_addr) {
	((int*)(arr))[index] = *(int*)elem_addr;
}

void append_array_double(void* arr, int index, void* elem_addr) {
	((double*)(arr))[index] = *(double*)elem_addr;
}


void init_dynamic_array(DYNAMIC_ARRAY* arr, int elems_size) {
	arr->size = 1;
	arr->current = -1;
	arr->elems = malloc(elems_size * arr->size);
}

void push_dynamic_array( DYNAMIC_ARRAY* arr, void* elem_addr,
						 void (*append_func)(void* arr, int index, void* elem_addr), int elem_size ) {

	arr->current++;

	if (arr->current > arr->size - 1) {
		arr->size += DYNAMIC_ARR_INC_UNIT;
		realloc(arr->elems, arr->size * elem_size);
	}
	append_func(arr->elems, arr->current, elem_addr);
}

void pop_dynamic_array(DYNAMIC_ARRAY* arr) {
	arr->current--;
}

void release_dynamic_array(DYNAMIC_ARRAY* arr) {
	free(arr->elems);
	arr->elems = NULL;
}
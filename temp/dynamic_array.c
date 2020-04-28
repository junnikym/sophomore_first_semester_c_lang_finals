#include "dynamic_array.h"

// ------------------------------------------------------- //
// ----- dyn_arr functions	------------------------------

void dyn_arr_init( DYN_ARR* a, int type_size ) {
	a->type_size = type_size;
	a->capacity	= __VECTOR_INIT_CAPPACITY;
	a->size		= -1;
	a->items	= malloc(type_size * a->capacity);
}

int dyn_arr_size( const DYN_ARR* a ) {
	return a->size;
}

static void dyn_arr_resize( DYN_ARR* a, int capacity ) {
	void* items = realloc(a->items, a->type_size * capacity);
	if(items == NULL) {
		/* ! TODO : Error Code */
	}

	a->items = items;
	a->capacity = capacity;
}

void dyn_arr_push_back( DYN_ARR* a, const void* elem, void (*copy__)(void*, const void*) ) {
	a->size++;

	if(a->capacity == a->size)
		dyn_arr_resize( a, a->capacity * 2 );
	
	copy__( (a->items + (a->type_size * a->size)), elem );
}

void dyn_arr_insert( DYN_ARR* a, int index, void* elem, void (*copy__)(void*, const void*) ) {
	if(index >= 0 && index < a->size)
		copy__((a->items + (a->type_size * index)), elem);
	else {
		/* ! TODO : Error Code */
	}
}

void* dyn_arr_get( const DYN_ARR* a, int index ) {
	void* addr = (a->items + (a->type_size * a->size));

	if(index >= 0 && index <= a->size) {
		printf("in get function : %p \n", addr);
		return addr;
	}

	return NULL;
}

void* dyn_arr_back( const DYN_ARR* a ) {
	return (a->items + (a->type_size * a->size));
}

void dyn_arr_delete( DYN_ARR* a, int index, void (*copy__)(void*, const void*) ) {
	int i = 0;
	void* i_ptr = NULL;
	
	if( (index < 0) || (index >= a->size) )
		return;	

	for(i = 0; i < a->size; i++) {
		i_ptr = (a->items + (a->type_size * i));
		copy__( i_ptr, i_ptr + a->type_size );
	}
	a->size--;

	if( (a->size > 0) && (a->size == a->capacity / 4) ) 
		dyn_arr_resize(a, a->capacity / 2);
}

void dyn_arr_release( DYN_ARR* a) {
	free(a->items);
	a->items = NULL;
}

// ------------------------------------------------------- //
// ----- Basic Type's copy function	----------------------

void copy_int( void* lhs, const void* rhs ) {
	*(int*)lhs = *(int*)rhs;
}

// ------------------------------------------------------- //
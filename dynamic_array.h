#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>

#include <stdio.h>

#define __VECTOR_INIT_CAPPACITY 4;

typedef struct _DYNAMIC_ARRAY {
    void* items;
    int capacity;
    int size;

    int type_size;
} DYN_ARR;

// ------------------------------------------------------- //
// ----- dyn_arr functions	------------------------------ 

void        dyn_arr_init        ( DYN_ARR* a, int type_size );
int         dyn_arr_size        ( const DYN_ARR* a );
static void dyn_arr_resize      ( DYN_ARR* a, int capacity );
void        dyn_arr_push_back   ( DYN_ARR* a, const void* elem, void (*copy__)(void*, const void*) );
void        dyn_arr_insert      ( DYN_ARR* a, int index, void* elem, void (*copy__)(void*, const void*) );
void*       dyn_arr_get         ( const DYN_ARR* a, int index );
void*       dyn_arr_back        ( const DYN_ARR* a );
void        dyn_arr_delete      ( DYN_ARR* a, int index, void (*copy__)(void*, const void*) );
void        dyn_arr_release     ( DYN_ARR* a);

void        dyn_arr_foreach     ( DYN_ARR* a, void* msger, void (*func)(void* elem, int i, void* arg) );

// ------------------------------------------------------- //
// ----- Basic Type's copy function	---------------------- 

void copy_int( void* lhs, const void* rhs );

// ------------------------------------------------------- //

#endif
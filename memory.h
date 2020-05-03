#ifndef MEMORY_H
#define MEMORY_H

#include "object.h"

static DYN_ARR g_objects;
static OBJECT* g_user_obj;

// ------------------------------------------------------- //
// ----- g_object functions	------------------------------

// -- push_back elements into g_object

void 	push_obj_to_g_obj 	( OBJECT* elem );
int 	push_ent_to_g_obj 	( ENTITY* elem, int obj_index );				//	ERROR CODE : -1
int 	push_force_to_g_obj	( FORCE* elem, int obj_index, int ent_index );	//	ERROR CODE : -1

// -- wapper

void 	g_obj_foreach( void (*func)(void* elem, int i, DYN_ARR* arr) );

// ------------------------------------------------------- //
// ----- entire memory functions	----------------------

void init_memory ( );
void release_memory();

// ------------------------------------------------------- //

#endif
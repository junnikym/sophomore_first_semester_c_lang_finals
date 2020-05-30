#ifndef MEMORY_H
#define MEMORY_H

#include "object.h"

static DYN_ARR g_objects;
static OBJECT g_user_obj;

// ------------------------------------------------------- //
// ----- g_object functions	------------------------------

// -- push_back elements into g_object

void 	push_obj_into_g_obj 	( OBJECT* elem );
int 	push_ent_into_g_obj 	( ENTITY* elem, int obj_index );				//	ERROR CODE : -1
int 	push_force_into_g_obj	( FORCE* elem, int obj_index, int ent_index );	//	ERROR CODE : -1

void	update_each_g_obj		( void* elem, int i, void* pos );
void	update_g_obj			( );

// -- wapper

void	g_obj_set_center		( int obj_index, int ent_index);

void 	g_obj_foreach		( void* msger, void (*func)(void* elem, int i, void* arg) );

VEC2	g_obj_get_position	( int index );

// ------------------------------------------------------- //
// ----- entire memory functions	----------------------

void init_memory ( );
void release_memory();

// ------------------------------------------------------- //

#endif

#ifndef MEMORY_H
#define MEMORY_H

#include <stdarg.h>

#include "object.h"
#include "types.h"

#define __CENTER_ENTITY -1

static DYN_ARR g_objects;
static OBJECT* g_user_obj;
static int g_user_obj_i;

// ------------------------------------------------------- //
// ----- g_object functions	------------------------------

// -- push_back elements into g_object

void*	g_obj_push_thing		( _OBJ_ELEM_ type, void* item, ... );	// ... => index of thing

OBJECT*	g_obj_set_user_obj		( int i );
ENTITY* g_obj_set_center_ent	( int obj_i, int ent_i );
void  	g_obj_set_essential_f 	( int obj_i, int ent_i );

void	update_each_g_obj		( void* elem, int i, void* pos );
void	update_g_obj			( );

void* 	g_obj_alter				( _OBJ_ELEM_ type, void* elem, ... );

void*	g_obj_get_thing			( _OBJ_ELEM_ type, ... );				// ... => index of thing

void 	g_obj_foreach		( void* msger, void (*func)(void* elem, int i, void* arg) );
VEC2	g_obj_get_position	( int index );

// ------------------------------------------------------- //
// ----- entire memory functions	----------------------

void init_memory ( );
void release_memory();

// ------------------------------------------------------- //

#endif

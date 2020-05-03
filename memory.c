#include "memory.h"

// ------------------------------------------------------- //
// ----- g_object function	------------------------------

// -- push_back elements into g_object

void push_obj_to_g_obj ( OBJECT* elem ) {
	dyn_arr_push_back( &g_objects, elem, copy_obj);
}

int push_ent_to_g_obj ( ENTITY* elem, int obj_index ) {
	if ( obj_index < 0 && obj_index > g_objects.size )
		return -1;		// ERROR
	
	dyn_arr_push_back(
		&((OBJECT*)g_objects.items)[obj_index].entities,
		elem,
		copy_ent
	);

	return 0;
}

int push_force_to_g_obj ( FORCE* elem, int obj_index, int ent_index ) {
	OBJECT* obj_converter = NULL;
	ENTITY* ent_converter = NULL;

	// ----- is in range 	---------------
	if ( obj_index < 0 && obj_index > g_objects.size ) 
		return -1;		// ERROR

	obj_converter = g_objects.items;
	if ( ent_index < 0 && ent_index > obj_converter[obj_index].entities.size ) 
		return -1;		// ERROR
	// ------------------------------------ //

	ent_converter = obj_converter[obj_index].entities.items;

	dyn_arr_push_back(
		&ent_converter[ent_index].forces,
		elem,
		copy_force
	);

	return 0;
}

// ------------------------------------------------------- //
// ----- entire memory functions	----------------------

void init_memory ( ) {
	dyn_arr_init( &g_objects, sizeof(OBJECT) );
}

void release_memory() {
	int i = 0;
	OBJECT* obj_converter = (OBJECT*)g_objects.items;

	for ( i = 0; i <= g_objects.size; i++ ) {
		release_obj( &obj_converter[i]);
	}
	obj_converter = NULL;

	dyn_arr_release( &g_objects );
}

// -- wapper

void g_obj_foreach( void (*func)(void* elem, int i, DYN_ARR* arr) ) {
	dyn_arr_foreach( &g_objects, func );
}

// ------------------------------------------------------- //

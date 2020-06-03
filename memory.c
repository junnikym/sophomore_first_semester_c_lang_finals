#include "memory.h"

// ------------------------------------------------------- //
// ----- g_textures functions	--------------------------

void* g_buf_obj_load ( const char* title,
					   GLuint texture,
					   const BUFFER_ATTRIBUTES* attr ) {
	TREE* inserter = NULL;
	
	if ( (inserter = tree_create( title, /* BUF_OBJ */ )) == NULL )
		return NULL;
	
	tree_insert( g_textures, inserter );
	
	return inserter;
}

void* g_buf_obj_load_comp	( FILE* file ) {
	/*
	 *	load texture infomation from compilation file
	 */
	return NULL;
}

// ------------------------------------------------------- //
// ----- g_object function	------------------------------

// -- push_back elements into g_object

void* g_obj_push_thing ( _OBJ_ELEM_ type, void* item, ... ) {
	va_list ap;
	va_start(ap, item);

	int i = 0;
	void* target = NULL;

	switch ( type ) {
		// --------------------------------------------------
		case __FORCE__:
			// -- Get chosen OBJECT
			i = va_arg ( ap, int );
			
			if ( i < 0 && i > g_objects.size ) {	// is in range
				printf("ERROR in g_obj_push_thing func -> out of range \n");
				printf("\t push : FORCE / error : g_objects index \n");
				return NULL;		// ERROR
			}
			
			target = dyn_arr_get(&g_objects, i);
			
			// -- Get chosen ENTITY
			i = va_arg ( ap, int );
			
			if( i == __CENTER_ENTITY ) {
				target = ((OBJECT*)target)->center;
			}
			else {
				if ( i < 0 && i > ((OBJECT*)target)->entities.size ) {	// is in range
					printf("ERROR in g_obj_push_thing func -> out of range \n");
					printf("\t push : FORCE / error : ENTITY index \n");
					return NULL;	// ERROR
				}
			
				target = dyn_arr_get( &((OBJECT*)target)->entities, i );
			}
			
			// -- push and return result
			target = &((ENTITY*)target)->forces;
			return dyn_arr_push_back ( target, item, copy_ent );
		// --------------------------------------------------
		case __ENTITY__:
			i = va_arg(ap, int);
			
			// -- is in range
			if ( i < 0 && i > g_objects.size )
				return NULL;

			// -- push and result
			target = &((OBJECT*)g_objects.items)[i].entities;
			return dyn_arr_push_back ( target, item, copy_ent );
		// --------------------------------------------------
		case __OBJECT__:
			return dyn_arr_push_back ( &g_objects, item, copy_obj );
		// --------------------------------------------------
	}

	return NULL;
}


// -- Setter

OBJECT* g_obj_set_user_obj ( int i ) {
	g_user_obj_i = i;
	g_user_obj = dyn_arr_get ( &g_objects, i );

	return g_user_obj;
}

ENTITY* g_obj_set_center_ent ( int obj_i, int ent_i ) {
	return set_center_obj ( dyn_arr_get ( &g_objects, obj_i ), ent_i );
}

void* g_obj_alter ( _OBJ_ELEM_ type, void* elem, ... ) {
	va_list ap;
	
	int i = 0;
	void* target = NULL;
	
	va_start(ap, elem);
	
	// -- Get OBJECT
	i = va_arg ( ap, int );		// OBJECT[i]
	
	target = dyn_arr_get( &g_objects, i );
	
	switch ( type ) {
		case __FORCE__:
			// -- Get ENTITY
			i = va_arg ( ap, int );		// OBJECT[i] -> ENTITY[i]
			
			if( i == __CENTER_ENTITY )
				target = ((OBJECT*)target)->center;
			else
				target = dyn_arr_get( &(((OBJECT*)target)->entities), i );
			
			// -- Get FORCE
			i = va_arg ( ap, int );		// OBJECT[i] -> ENTITY[i] -> FORCE[i]
			target = dyn_arr_get( &(((ENTITY*)target)->forces), i );
			
			// -- Alter
			copy_force ( target, elem );
			
			return target;
		case __ENTITY__:
			i = va_arg ( ap, int );		// OBJECT[i] -> ENTITY[i]
			
			if( i == __CENTER_ENTITY )
				target = ((OBJECT*)target)->center;
			else
				target = dyn_arr_get( &(((OBJECT*)target)->entities), i );
			
			copy_ent ( target, elem );
			
			return target;
		case __OBJECT__:
			copy_obj ( target, elem );
			
			return target;
	}
	
	return NULL;
}

void g_obj_set_essential_f ( int obj_i, int ent_i ) {
	void* target = dyn_arr_get (&g_objects, obj_i);
	
	if(ent_i == -1)
		target = ((OBJECT*)target)->center;
	else
		target = dyn_arr_get( &(((OBJECT*)target)->entities), ent_i );
	
	set_essential_f_ent(target);
}

// -- Update functions

void update_each_g_obj ( void* elem, int i, void* arg ) {
	update_obj ( elem );
}

void update_g_obj ( ) {
	g_obj_foreach( NULL, update_each_g_obj );
}

void g_obj_foreach ( void* msger, void (*func)(void* elem, int i, void* arg) ) {
	dyn_arr_foreach(&g_objects, msger, func);
}

VEC2 g_obj_get_position(int index) {
	return ((OBJECT*)g_objects.items)[index].center->position;
}


// ------------------------------------------------------- //
// ----- entire memory functions	----------------------

void init_memory ( ) {
	g_buf_objs = NULL;
	
	dyn_arr_init( &g_objects, sizeof(OBJECT) );
	g_user_obj = NULL;
	g_user_obj_i = -1;
}

void release_memory() {
	int i = 0;
	OBJECT* obj_converter = NULL;
	
	obj_converter = (OBJECT*)g_objects.items;

	for ( i = 0; i <= g_objects.size; i++ ) {
		release_obj( &obj_converter[i]);
	}
	obj_converter = NULL;

	dyn_arr_release( &g_objects );
	
	tree_release( g_buf_objs, 1 );
}

// ------------------------------------------------------- //

#include "memory.h"

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
			i = va_arg ( ap, int );
			// -- is in range
			if ( i < 0 && i > g_objects.size )
				return NULL;		// ERROR

			target = &((OBJECT*)g_objects.items)[i];
			i = va_arg ( ap, int );
			if ( i < 0 && i > ((OBJECT*)target)->entities.size )
				return -1;		// ERROR

			// -- push and result
			target = &( (ENTITY*) ( ((OBJECT*)target)->entities.items ) )[i].forces;
			
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
	set_center_obj ( dyn_arr_get ( &g_objects, obj_i ), ent_i );
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
	dyn_arr_init( &g_objects, sizeof(OBJECT) );
	init_obj( &g_user_obj );
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

// ------------------------------------------------------- //

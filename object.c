#include "object.h"

// ------------------------------------------------------- //
// ----- object functions	------------------------------

void init_obj ( OBJECT* obj ) {
	dyn_arr_init( &(obj->entities), sizeof(ENTITY) );
	
	obj->center = NULL;
	obj->direction = NULL;
} 

void copy_obj( void* lhs, const void* rhs) {
	if(rhs == NULL) 
		init_obj( (OBJECT*)lhs );
	else
		*(OBJECT*)lhs = *(OBJECT*)rhs;
}

void release_obj ( OBJECT* obj ) {
	int i = 0;
	ENTITY* ent_converter = (ENTITY*)(obj->entities.items);

	for( i = 0; i <= obj->entities.size; i++) {
		printf("release entity [%d] \n", i);
		release_ent( &ent_converter[i] );
	}

	dyn_arr_release( &obj->entities );

	obj->center = NULL;
	obj->direction = NULL;
}

void adapt_each_f_obj (void* elem, int i, void* pos) {
	VEC2 ent_f = pass_by_f_ent ( elem );
	
	vec2_add_assn (
		pos,
		&ent_f
	);
}

void adapt_f_obj ( OBJECT* obj ) {
	VEC2 result = V2_ZERO;
	dyn_arr_foreach(&obj->entities, &obj->center->position, adapt_each_f_obj);
}

VEC2 pass_by_f_obj ( OBJECT* obj ) {
	VEC2 result = V2_ZERO;
	dyn_arr_foreach(&obj->entities, &result, adapt_each_f_obj);

	return result;
}

void update_each_obj (void* elem, int i, void* pos) {
	adapt_each_f_obj ( elem, i, pos );
	draw_ent( elem );
}

void update_obj ( OBJECT* obj ) {
	dyn_arr_foreach(&obj->entities, &obj->center->position, update_each_obj);
}

// -- setting function

void* set_center_obj ( OBJECT* obj, int index ) {
	if (obj->center != NULL) {
		// !TODO : detech_center_obj();
	}
	void* a = dyn_arr_get(&obj->entities, index);
	
	return (obj->center = a);
}

void detech_center_obj ( OBJECT* obj ) {
	
}

// ------------------------------------------------------- //

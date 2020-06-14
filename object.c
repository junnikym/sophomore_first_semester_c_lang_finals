#include "object.h"

// ------------------------------------------------------- //
// ----- object functions	------------------------------

void init_obj ( OBJECT* obj ) {
	dyn_arr_init( &(obj->entities), sizeof(ENTITY) );
	obj->center = NULL;
	
	obj->collision_box = (VEC2){-1.0f, -1.0f};
	obj->collision_indicator = 0;
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
		release_ent( &ent_converter[i] );
	}

	dyn_arr_release( &obj->entities );

	obj->center = NULL;
}

void adapt_each_f_obj (void* elem, int i, void* msger) {
	MOMENTUM ent_momentum = pass_by_f_ent ( elem );
	
	*(((MOMENTUM_PTR*)msger)->angle) += ent_momentum.angle;

	vec2_add_assn (
		((MOMENTUM_PTR*)msger)->vector,
		&(ent_momentum.vector)
	);
}
   
void update_each_obj (void* elem, int i, void* msger) {
	adapt_each_f_obj ( elem, i, msger );
	
	draw_ent( elem );
}

void update_obj ( OBJECT* obj ) {
	MOMENTUM_PTR info_msger = {
		&(obj->center->position),
		&(obj->center->angle)
	};
	
	dyn_arr_foreach(&obj->entities, &info_msger, update_each_obj);
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
 

#include "object.h"

void append_array_object(void* arr, int index, void* elem_addr) {
	if (elem_addr == NULL) 
		init_object(&((OBJECT*)(arr))[index]);
	else 
		((OBJECT*)(arr))[index] = *(OBJECT*)elem_addr;
} 

void release_array_object(OBJECT* obj) {
	int i = 0;

	for (i = 0; i <= obj->entities.current; i++) {
		release_array_entity( &((ENTITY*)(obj->entities.elems))[i] );
	}

	release_dynamic_array(&obj->entities.elems);
}

void init_object(OBJECT* obj) {
	init_entity(&obj->entities);
	obj->center = NULL;
	obj->direction_force = NULL;
}

void set_center_obj(OBJECT* obj, int index) {
	DYNAMIC_ARRAY* force_ptr = NULL;
	
	if (obj->center != NULL) {
		// !TODO : detech_center_obj();
	}

	obj->center = &((ENTITY*)(obj->entities.elems))[index];

	push_dynamic_array(
		&(obj->center)->forces,
		&V2_ZERO,
		append_array_vec2,
		sizeof(VEC2)
	);
	
	force_ptr = &obj->center->forces;
	obj->direction_force = &((VEC2*)(force_ptr->elems))[force_ptr->current];
}


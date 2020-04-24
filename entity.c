#include "entity.h"

void append_array_entity(void* arr, int index, void* elem_addr) {
	if (elem_addr == NULL) 
		init_entity(&((ENTITY*)(arr))[index]);
	else
		((ENTITY*)(arr))[index] = *(ENTITY*)elem_addr;
}

void release_array_entity(ENTITY* ent) {
	release_dynamic_array(&ent->forces);
}

void init_entity(ENTITY* ent) {
	init_dynamic_array(&ent->forces, sizeof(VEC2));
	ent->position		= V2_ZERO;
	ent->direction_vec	= V2_ZERO;
}

void push_ent(DYNAMIC_ARRAY* ents, void* elem) {
	push_dynamic_array(
		&ents,
		elem,
		append_array_entity,
		sizeof(ENTITY)
	);
}
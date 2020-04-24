#include "memory.h"

void setting_for_test() {
	push_g_obj(NULL);
	g_user_obj = &((OBJECT*)(g_objects.elems))[g_objects.current];

	push_ent(&g_user_obj->entities, NULL);
	set_center_obj(g_user_obj, g_user_obj->entities.current);
}

void init_memory() {
	init_dynamic_array(&g_objects, sizeof(OBJECT));
}

void push_g_obj(void* elem) {
	push_dynamic_array(
		&g_objects,
		elem,
		append_array_object,
		sizeof(OBJECT)
	);
}

void release_memory() {
	int i = 0, j = 0;

	// g_object
	for (i = 0; i <= g_objects.current; i++) {
		release_array_object( &((OBJECT*)(g_objects.elems))[i] );
	}

	release_dynamic_array(&g_objects);
}

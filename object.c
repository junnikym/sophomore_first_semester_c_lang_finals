#include "object.h"

void append_array_object(void* arr, int index, void* elem_addr) {
	((OBJECT*)(arr))[index] = *(OBJECT*)elem_addr;
} 

void init_object(OBJECT* obj) {
	init_dynamic_array(&obj->entities, sizeof(ENTITY));
	obj->center = NULL;
}

void set_center_obj(OBJECT* obj, int index) {
	obj->center = &((ENTITY*)(obj->entities.elems))[index];
}


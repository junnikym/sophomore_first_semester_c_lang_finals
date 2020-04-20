#include "entity.h"

void append_array_entity(void* arr, int index, void* elem_addr) {
	((ENTITY*)(arr))[index] = *(ENTITY*)elem_addr;
}

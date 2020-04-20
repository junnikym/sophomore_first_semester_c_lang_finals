#ifndef OBJECT_H
#define OBJECT_H

#include "dynamic_array.h"
#include "entity.h"

typedef struct {
	DYNAMIC_ARRAY entities;
	ENTITY* center;
} OBJECT;

void append_array_object(void* arr, int index, void* elem_addr);

void init_object(OBJECT* obj);
void set_center_obj(OBJECT* obj, int index);

#endif
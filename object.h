#ifndef OBJECT_H
#define OBJECT_H

#include "dynamic_array.h"
#include "entity.h"

typedef struct {
	DYNAMIC_ARRAY entities;
	ENTITY* center;
	VEC2* direction_force;
} OBJECT;

void append_array_object(void* arr, int index, void* elem_addr);
void release_array_object(OBJECT* obj);

void init_object(OBJECT* obj);
void set_center_obj(OBJECT* obj, int index);
void detech_center_obj(OBJECT* obj);

#endif
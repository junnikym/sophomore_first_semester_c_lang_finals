#ifndef ENTITY_H
#define ENTITY_H

#include "types.h"
#include "dynamic_array.h"

typedef struct _ENTITY {
    VEC2 position;
    VEC2 direction_vec;
    DYNAMIC_ARRAY forces;   // VEC2

    // !TODO : Create attribute; (mass, meterial, ... )
} ENTITY;

void append_array_entity(void* arr, int index, void* elem_addr);
void release_array_entity(ENTITY* ent);

void init_entity(ENTITY* ent);

void push_ent(DYNAMIC_ARRAY* ents, void* elem);

#endif
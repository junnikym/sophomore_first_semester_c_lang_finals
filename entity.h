#ifndef ENTITY_H
#define ENTITY_H

#include "types.h"

typedef struct _ENTITY {
    VEC2 position;
    VEC2 direction_vec;
    VEC2* force_vec;
} ENTITY;

void append_array_entity(void* arr, int index, void* elem_addr);

#endif
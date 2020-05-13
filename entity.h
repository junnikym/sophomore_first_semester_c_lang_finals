#ifndef ENTITY_H
#define ENTITY_H

#include "force.h"
#include "dynamic_array.h"

typedef struct _ENTITY {
    VEC2 position;
    VEC2 direction_vec;
    DYN_ARR forces;   // VEC2

    // !TODO : Create attribute; (mass, meterial, ... )
} ENTITY;

void init_ent       ( ENTITY* ent );
void release_ent    ( ENTITY* ent );

void copy_ent       ( void* lhs, const void* rhs );

void adapt_each_f_ent ( void* f_in_e, int i, void* pos );
void adapt_f_ent    ( ENTITY* ent );
VEC2 pass_by_f_ent  ( ENTITY* ent );

#endif
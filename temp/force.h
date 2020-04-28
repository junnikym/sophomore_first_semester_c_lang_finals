#ifndef FORCE_H
#define FORCE_H

#include "types.h"

#include <stdlib.h>

typedef struct _FORCE {
    VEC2 force_vec;
    int identify;
    double delta_t;
} FORCE;

void copy_force(void* lhs, const void* rhs);

void init_force( FORCE* f );
void set_vec_force( FORCE* f, double x, double y );

#endif
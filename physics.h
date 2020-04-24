#ifndef PHYSICS_H
#define PHYSICS_H

#include "types.h"

#include <math.h>

enum __PHY_FLAGS__ {
    GRAVITY = 1 << 0,
    FRICTION = 1 << 1,
} _PHY_FLAGS_;

typedef struct _FORCE {
    VEC2 force_vec;
    int identify;
    double delta_t;
} FORCE;

void append_array_force(void* arr, int index, void* elem_addr);

void accelerate( VEC2 position, VEC2 accel );

//void gravity(const double* gravity_constant );

void friction(VEC2* force, const double* constant);

#endif
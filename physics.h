#ifndef PHYSICS_H
#define PHYSICS_H

#include "types.h"
#include "force.h"

#include <math.h>

typedef enum __PHY_FLAGS__ {
    GRAVITY = 1 << 0,
    FRICTION = 1 << 1,
} _PHY_FLAGS_;

void accelerate( VEC2 position, VEC2 accel );

// -- Transform force
void transform_to_gravity( VEC2* g_force, const double* gravity_constant );

// -- Applay to force 
void friction( VEC2* force, const double* constant );

#endif
#ifndef PHYSICS_H
#define PHYSICS_H

#include "types.h"
#include "force.h"

#include <math.h>

enum __PHY_FLAGS__ {
    GRAVITY = 1 << 0,
    FRICTION = 1 << 1,
} _PHY_FLAGS_;

void accelerate( VEC2 position, VEC2 accel );

//void gravity(const double* gravity_constant );

void friction(VEC2* force, const double* constant);

#endif
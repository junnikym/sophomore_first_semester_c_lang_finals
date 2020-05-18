#ifndef PHYSICS_H
#define PHYSICS_H

#include "types.h"
#include "force.h"
#include "entity.h"

#include <math.h>

typedef enum __PHY_FLAGS__ {
    GRAVITY = 1 << 0,
    FRICTION = 1 << 1,
} _PHY_FLAGS_;

// -- Transform force
void transform_to_gravity( VEC2* g_force, const double* gravity_constant );

// -- Applay to force 
void friction( VEC2* force, const double* constant );


void run_all_phy ( ENTITY* ent );

#endif

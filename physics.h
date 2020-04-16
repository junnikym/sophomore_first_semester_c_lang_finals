#ifndef PHYSICS_H
#define PHYSICS_H

#include "types.h"

#include <math.h>

void accelerate( VEC2 position, VEC2 accel );

//void gravity(const double* gravity_constant );

void friction(VEC2* force, const double* constant);

#endif
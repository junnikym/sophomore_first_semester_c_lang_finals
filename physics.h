#ifndef PHYSICS_H
#define PHYSICS_H

#include "vector2.h"
#include "force.h"

#include <math.h>

// -- (append / update) force
void transform_to_gravity ( FORCE* f,
						    const double* gravity_constant,
						    const VEC2* gravity_direction );

// -- Apply to force 
void friction( VEC2* force, const double* constant );

// -- checking function
void collision_detection_aabb ( );

#endif

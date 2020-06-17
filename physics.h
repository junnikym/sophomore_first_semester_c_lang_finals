#ifndef PHYSICS_H
#define PHYSICS_H

#include "vector2.h"
#include "force.h"

#include <math.h>

// 16 = 1 << 5
#define __NO_COLLIDE 0x10

#define __COLLISION_DETECTED_Y 			0x1
#define __COLLISION_DETECTED_X 			0x4
#define __COLLISION_DETECTED_OTHER_Y	0x2
#define __COLLISION_DETECTED_OTHER_X	0x8

// -- (append / update) force
void transform_to_gravity ( FORCE* f,
						    const double* gravity_constant,
						    const VEC2* gravity_direction );

// -- Apply to force 
void friction( VEC2* force, const double* constant );

// -- checking function
int collision_detection_obb ( const VEC2* lhs_pos,
							  const VEC2* lhs_size,
							  const double* lhs_angel,
							  const VEC2* rhs_pos,
							  const VEC2* rhs_size,
							  const double* rhs_angle );

#endif

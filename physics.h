#ifndef PHYSICS_H
#define PHYSICS_H

#include "vector2.h"
#include "force.h"

#include <math.h>

// 출돌에 검사 결과 어떤상태인지 알려주기 위해 비트플래그를 활용
// 16 = 1 << 5
#define __NO_COLLIDE 0x10

#define __COLLISION_DETECTED_Y 			0x1
#define __COLLISION_DETECTED_X 			0x4
#define __COLLISION_DETECTED_OTHER_Y	0x2
#define __COLLISION_DETECTED_OTHER_X	0x8

// 충돌 시 허용 오차 범위
#define __COLLISION_EPSILON				0.0001

// -- (append / update) force

	// 인자로 넘어온 force를 중력역할을 할 수 있도록 바꾸어줌
void transform_to_gravity ( FORCE* f,
						    const double* gravity_constant,
						    const VEC2* gravity_direction );

// -- Apply to force

	// 인자로 넘어온 force에 마찰력을 적용시켜줌.
void friction( VEC2* force, const double* constant );

// -- checking collision function

	// 선과 선간의 충돌
int intersection_line ( const double lhs_slope,
						const double lhs_height,
						const double rhs_slope,
						const double rhs_height,
						VEC2* result );

	// OOB 충돌 : 각도가 있는 네모 간의 충돌
int collision_detection_obb ( const VEC2* lhs_pos,
							  const VEC2* lhs_size,
							  const double* lhs_angel,
							  const VEC2* rhs_pos,
							  const VEC2* rhs_size,
							  const double* rhs_angle );

	// 원과 원 사이의 충돌
int collision_detection_circle ( const VEC2* lhs_pos, 
								 const double* lhs_range,
								 const VEC2* rhs_pos, 
								 const double* rhs_range );

	// 원과 네모 간의 충돌
int collision_detection_cir_box ( const VEC2* circle_pos,
								  const double* circle_range,
								  const VEC2* box_pos,
								  const VEC2* box_size,
								  const double* box_angle );

#endif

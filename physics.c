#include "physics.h"

void append_array_force(void* arr, int index, void* elem_addr) {
    ((FORCE*)(arr))[index] = *(FORCE*)elem_addr;
}

// -- (append / update) force

void transform_to_gravity( FORCE* f,
						   const double* gravity_constant,
						   const VEC2* gravity_direction ) {

	f->identify = (__F_PHY_GRAVITY__);
	
	f->accel_vec = vec2_mul( gravity_direction, *gravity_constant );
}

// -- Apply to force

void friction(VEC2* force, const double* constant) {
	vec2_mul_assn(force, *constant);
}

// -- checking collision function

int intersection_line ( double lhs_slope,
						double lhs_height,
						double rhs_slope,
						double rhs_height,
						VEC2* result ) {

	if(lhs_slope == rhs_slope) 
		return -1;

	result->x = (rhs_height -lhs_height) / (rhs_slope - lhs_slope);
	result->y = lhs_slope * result->x + lhs_height;

	return 0;
}

int collision_detection_obb ( const VEC2* lhs_pos,
								    const VEC2* lhs_size,
								    const double* lhs_angle,
								    const VEC2* rhs_pos,
								    const VEC2* rhs_size,
								    const double* rhs_angle ) {
	int i = 0;	int j = 0;
	double sum = 0;
	
	int collision_flag = 0;
	
	VEC2 dist = vec2_get_distance(lhs_pos, rhs_pos);
	VEC2 vec[4] = {
		vec2_get_height(lhs_size, lhs_angle),
		vec2_get_height(rhs_size, rhs_angle),
		vec2_get_width(lhs_size, lhs_angle),
		vec2_get_width(rhs_size, rhs_angle)
	};
	
	VEC2 unit = V2_ZERO;
	
	for ( i = 0; i < 4; i++ ) {
		sum = 0;
		unit = vec2_get_unit( &vec[i] );
		
		for ( j = 0; j < 4; j++ )
			sum += vec2_dot( &vec[j], &unit );
		
		if ( vec2_dot( &dist, &unit ) > sum ) {
			collision_flag |= __NO_COLLIDE;
		}
		else {
			collision_flag |= 1 << i;
		}
	}
	
	printf(" in collision function : flag : %d \n", collision_flag);
	
	return collision_flag;
}

int collision_detection_circle ( const VEC2* lhs_pos,
								 const double* lhs_range,
								 const VEC2* rhs_pos,
								 const double* rhs_range ) {
	double length = 0;
	VEC2 temp_4_length = vec2_sub(lhs_pos, rhs_pos);

	// 두 원의 중심 간의 거리를 계산
	length = sqrt(SQUARE(temp_4_length.x) + SQUARE ( temp_4_length.y ));

	if ( length <= (*lhs_range - *rhs_range) ) {
		return 0;	// 두 원의 거리가 두원이 접한 최대 거리보다 작을 시 충돌
	}

	return __NO_COLLIDE;
}

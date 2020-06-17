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
	
	printf("");
	
	return collision_flag;
}

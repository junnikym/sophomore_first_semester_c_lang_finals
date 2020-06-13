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

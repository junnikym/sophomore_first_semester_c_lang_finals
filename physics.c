#include "physics.h"

void append_array_force(void* arr, int index, void* elem_addr) {
    ((FORCE*)(arr))[index] = *(FORCE*)elem_addr;
}

// -- (append / update) force
void transform_to_gravity( VEC2* g_force, const double* gravity_constant ) {
	
}

// -- Apply to force
void friction(VEC2* force, const double* constant) {
    vec2_mul_assn(force, *constant);
}

void run_all_phy() {

}
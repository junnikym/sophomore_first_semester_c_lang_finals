#include "physics.h"

void append_array_force(void* arr, int index, void* elem_addr) {
    ((FORCE*)(arr))[index] = *(FORCE*)elem_addr;
}

// -- (append / update) force
void transform_to_gravity( FORCE* f, const double* g_constant, VEC2* g_direction ) {
	f->force_vec = vec2_mul ( g_direction, *g_constant );

    if ( !(f->identify & __F_PHY_GRAVITY) ) {
        f->identify |= __F_PHY_GRAVITY;
    }

    //	 ¨ö¤ýg¤ýt©÷¤ým
}

// -- Apply to force
void friction(VEC2* force, const double* constant) {
    vec2_mul_assn(force, *constant);
}

void run_all_phy ( ENTITY* ent ) {

}
#include "physics.h"

void append_array_force(void* arr, int index, void* elem_addr) {
    ((FORCE*)(arr))[index] = *(FORCE*)elem_addr;
}

void accelerate(VEC2 position, VEC2 accel) {
    
}

void transform_to_gravity( VEC2* g_force, const double* gravity_constant ) {

}

void friction(VEC2* force, const double* constant) {
    vec2_mul_assn(force, *constant);
}
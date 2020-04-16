#include "physics.h"

void accelerate(VEC2 position, VEC2 accel) {
    
}

void friction(VEC2* force, const double* constant) {
    vec2_mul_assn(force, *constant);
}
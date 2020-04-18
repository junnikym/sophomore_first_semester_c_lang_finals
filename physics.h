#ifndef PHYSICS_H
#define PHYSICS_H

#include "types.h"

#include <math.h>

enum PHY_FLAGS {
    GRAVITY = 1 << 0,
    FRICTION = 1 << 1,
};

typedef struct _FORCE {
    VEC2 force_vec;
    int identify;
    double delta_t;
} FORCE;

typedef struct _FORCE_ARRAY {
    FORCE* elems;
    int size;
    int current;
} FORCE_ARRAY;

// manage force
void init_force_arr(FORCE_ARRAY* arr);
void push_force_arr(FORCE_ARRAY* arr, VEC2 vec, int id);
void pop_force_arr(FORCE_ARRAY* arr);
void release_force_arr(FORCE_ARRAY* arr);

void accelerate( VEC2 position, VEC2 accel );

//void gravity(const double* gravity_constant );

void friction(VEC2* force, const double* constant);

#endif
#ifndef FORCE_H
#define FORCE_H

#include "identify.h"
#include "types.h"

#include <stdlib.h>
#include <GL/glew.h>
#include  <GLFW/glfw3.h>

#define FORCE_IDENTITY_INIT     {V2_ZERO, -1, 0}

typedef enum __FORCE_FLAGS__ {
	F_ACCELERATE = 1 << 0,
	F_PAUSE = 1 << 0,
} _FORCE_FALGS_;

typedef struct _FORCE {
    VEC2 force_vec;
    int identify;			// INSERT FLAGS INTO FORCE->ID
	double start_t;
} FORCE;

FORCE 	generate_force( VEC2 f, int id );

void 	copy_force(void* lhs, const void* rhs);

void 	init_force( FORCE* f );
void 	set_vec_force( FORCE* f, double x, double y );

VEC2 	output_force ( FORCE* force, double t );

#endif

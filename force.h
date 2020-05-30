#ifndef FORCE_H
#define FORCE_H

#include "identify.h"
#include "types.h"
#include "vector2.h"
#include "dynamic_array.h"

#include <stdlib.h>
#include <GL/glew.h>
#include  <GLFW/glfw3.h>

#define FORCE_IDENTITY_INIT     {V2_ZERO, -1, 0}

typedef enum __FORCE_FLAGS__ {
	__F_ACCELERATE__	= 1 << 0,
	__F_PAUSE__			= 1 << 1,
	__F_FOR_CONTROL__	= 1 << 2,
} _FORCE_FALGS_;

typedef struct _FORCE {
    VEC2 force_vec;
    int identify;			// INSERT FLAGS INTO FORCE->ID
	double start_t;
} FORCE;

void 	copy_force		(void* lhs, const void* rhs);

void 	init_force		( FORCE* f );
void 	set_vec_force	( FORCE* f, double x, double y );

VEC2 	output_force 		( FORCE* force, double t );

FORCE*	search_id_force	( DYN_ARR* arr, int id );
FORCE 	generate_force	( VEC2 f, int id );

#endif

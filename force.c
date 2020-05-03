#include "force.h"

void copy_force(void* lhs, const void* rhs) {
	if ( rhs == NULL ) 
		init_force( (FORCE*)lhs );
	else
		*(FORCE*)lhs = *(FORCE*)rhs;
}

void init_force( FORCE* f ) {
	f->force_vec = V2_ZERO;
	f->identify = 0;
	f->delta_t = 0;
}

void set_vec_force( FORCE* f, double x, double y ) {
	f->force_vec.x = x;
	f->force_vec.y = y;
}

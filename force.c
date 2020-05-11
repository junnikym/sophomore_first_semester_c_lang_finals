#include "force.h"

void copy_force(void* lhs, const void* rhs) {
	if ( rhs == NULL ) 
		init_force( (FORCE*)lhs );
	else {
		*(FORCE*)lhs = *(FORCE*)rhs;
	}
}

FORCE generate_force( VEC2 f, int id) {
	return (FORCE){ f, id, 0 };
}

void init_force( FORCE* f ) {
	*f = (FORCE)FORCE_IDENTITY_INIT;
}

void set_vec_force( FORCE* f, double x, double y ) {
	f->force_vec.x = x;
	f->force_vec.y = y;
}

VEC2 output_force ( FORCE* f, double t ) {
	if( f->identify & (F_PAUSE << __FORCE_ENUM_SHIFTER) ) {
		f->start_t = 0.0;
		return V2_ZERO;
	}
	
	if( f->start_t == 0.0 )
		f->start_t = t;
	else {
		
		if( f->identify & (F_ACCELERATE << __FORCE_ENUM_SHIFTER) ) {
			return vec2_mul( &f->force_vec, SQUARE(t - f->start_t));
		}
	}
	
	return vec2_mul( &f->force_vec, (t - f->start_t));
}

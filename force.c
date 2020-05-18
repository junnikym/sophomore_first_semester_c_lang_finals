#include "force.h"

void copy_force(void* lhs, const void* rhs) {
	if ( rhs == NULL ) 
		init_force( (FORCE*)lhs );
	else {
		*(FORCE*)lhs = *(FORCE*)rhs;
	}
}

void init_force( FORCE* f ) {
	*f = (FORCE)FORCE_IDENTITY_INIT;
}

void set_vec_force( FORCE* f, double x, double y ) {
	f->force_vec.x = x;
	f->force_vec.y = y;
}

VEC2 output_force ( FORCE* f, double t ) {
	VEC2 result = V2_ZERO;
	
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

FORCE* search_id_force( DYN_ARR* arr, int id ) {
	int i = 0;
	FORCE* result = NULL;
	FORCE* converter = NULL;
	
	for(i = 0; i <= arr->size; i++) {
		converter = dyn_arr_get(arr, i);
		printf("id_on_conv : %d, id on arg : %d \n", converter->identify, id);
		
		if ( converter->identify & id ) {
			return converter;
		}
	}
	
	return result;
}

FORCE generate_force( VEC2 f, int id) {
	return (FORCE){ f, id, 0 };
}

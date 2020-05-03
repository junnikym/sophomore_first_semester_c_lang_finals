#include "entity.h"

void init_ent( ENTITY* ent ) {
	dyn_arr_init( &ent->forces, sizeof(FORCE) );

	ent->direction_vec = V2_ZERO;
	ent->position = V2_ZERO;
}

void copy_ent( void* lhs, const void* rhs ) {
	if(rhs == NULL)
		init_ent( (ENTITY*)lhs );
	else
		*(ENTITY*)lhs = *(ENTITY*)rhs;
}

void release_ent( ENTITY* ent) {
	dyn_arr_release( &ent->forces );
}
#include "entity.h"

void init_ent( ENTITY* ent ) {
	dyn_arr_init( &ent->forces, sizeof(FORCE) );

	ent->direction_vec = V2_ZERO;
	ent->position = V2_ZERO;
}

void release_ent( ENTITY* ent) {
	dyn_arr_release( &ent->forces );
}

void copy_ent( void* lhs, const void* rhs ) {
	if(rhs == NULL)
		init_ent( (ENTITY*)lhs );
	else
		*(ENTITY*)lhs = *(ENTITY*)rhs;
}

void adapt_each_f_ent ( void* f_in_e, int i, void* pos ) {
	VEC2 result_f = output_force( f_in_e, glfwGetTime() );
	
	vec2_add_assn (
		pos,
		&result_f
	);
}

void adapt_f_ent ( ENTITY* ent ) {
	dyn_arr_foreach ( &ent->forces, &ent->position, adapt_each_f_ent );
}

VEC2 pass_by_f_ent ( ENTITY* ent) {
	VEC2 result = V2_ZERO;
	dyn_arr_foreach ( &ent->forces, &result, adapt_each_f_ent );

	return result;
}

void set_essential_f_ent ( ENTITY* ent ) {
	FORCE inserter = (FORCE)FORCE_IDENTITY_INIT;
	
	dyn_arr_resize( &ent->forces, __N_ESSENTAL_FORCE );
	
	// -- CONTROL FORCES ------------
	inserter.identify = F_FOR_CONTROL;
	dyn_arr_insert( &ent->forces, 0, &inserter, copy_force);
	
	// -- PHY FORCES ----------------
	inserter.identify = F_FOR_CONTROL;
	dyn_arr_insert( &ent->forces, 1, &inserter, copy_force);
	
	// ------------------------------
	
	
}

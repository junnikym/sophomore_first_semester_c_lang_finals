#include "entity.h"

void init_ent( ENTITY* ent ) {
	dyn_arr_init( &ent->forces, sizeof(FORCE) );

	ent->direction_vec 	= V2_ZERO;
	ent->position 		= V2_ZERO;
	
	ent->graphics_buf 	= NULL;
	ent->texture_pos	= NULL;
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

// ! TODO : Modify -> summative entity ( entities that except center )
void draw_ent ( const ENTITY* ent ) {
	if(ent->graphics_buf == NULL)
		return;
	
	mat4 model = GLM_MAT4_IDENTITY_INIT;
	mat4 mvp = GLM_MAT4_IDENTITY_INIT;
	
	VEC2 frame_pos = (VEC2){1/16.0f, 1/16.0f};
	
	glm_translate_to(
		(mat4)GLM_MAT4_IDENTITY_INIT,
		(vec3) {
			ent->position.x,
			ent->position.y,
			0.0f
		},
		model
	);
	
	gl_update_cam();
	gl_get_mvp(model, mvp);
	
	// ! TODO : for test code
	gl_draw_sprite_obj ( ent->graphics_buf, *mvp, frame_pos );
}

void set_essential_f_ent ( ENTITY* ent ) {
	FORCE inserter = (FORCE)FORCE_IDENTITY_INIT;
	
	dyn_arr_resize( &ent->forces, __N_ESSENTAL_FORCE );
	
	// -- CONTROL FORCES ------------
	inserter.identify = __F_FOR_CONTROL__;
	if ( (ent->forces).size == -1 )
		dyn_arr_push_back( &ent->forces, &inserter, copy_force );
	
	dyn_arr_insert( &ent->forces, 0, &inserter, copy_force);
	
	// -- PHY FORCES ----------------
	inserter.identify = __F_FOR_CONTROL__;
	
	if ( (ent->forces).size == 0 )
		dyn_arr_push_back( &ent->forces, &inserter, copy_force );
	
	dyn_arr_insert( &ent->forces, 1, &inserter, copy_force);
	
	// ------------------------------
}

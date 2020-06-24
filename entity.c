#include "entity.h"

void ent_toggle_brake(void* ent, const void* brake) {
	int i = 0;
	ENTITY* e = (ENTITY*)ent;
	FORCE* f = NULL;

	if (e->is_breke != *(int*)brake) {
		e->is_breke = *(int*)brake;

		if (e->is_breke != 0) {
			for (i = 0; i <= e->forces.size; i++) {
				f = dyn_arr_get(&e->forces, i);
				f->identify |= __F_BRAKE__;
			}
		}
		else {
			for (i = 0; i <= e->forces.size; i++) {
				f = dyn_arr_get(&e->forces, i);
				f->identify ^= __F_BRAKE__;
			}
		}
	}
	
}

void init_ent( ENTITY* ent ) {
	dyn_arr_init( &ent->forces, sizeof(FORCE) );

	ent->angle 			= 0;
	ent->position 		= V2_ZERO;
	
	ent->graphics_buf 	= NULL;
	ent->texture_pos	= V2_ZERO;

	ent->buf_z			= 0.0;
	ent->blend_color[0] = 1.0f;
	ent->blend_color[1] = 1.0f;
	ent->blend_color[2] = 1.0f;
	ent->blend_color[3] = 1.0f;

	ent->animate = NULL;
	ent->is_breke = 0;
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

void modify_ent(void* lhs, const void* rhs) {
	if (rhs == NULL || lhs == NULL)
		return;

	else
		((ENTITY*)lhs)->position = *(VEC2*)rhs;
}

void modify_ent_texture_pos(void* lhs, const void* rhs) {
	if (rhs == NULL || lhs == NULL)
		return;

	else
		((ENTITY*)lhs)->texture_pos = *(VEC2*)rhs;
}

void set_blend_in_ent(void* lhs, const void* blend) {
	vec4 a = GLM_VEC4_ZERO_INIT;
	glm_vec4_copy(blend, a);

	((ENTITY*)lhs)->blend_color[0] = a[0];
	((ENTITY*)lhs)->blend_color[1] = a[1];
	((ENTITY*)lhs)->blend_color[2] = a[2];
	((ENTITY*)lhs)->blend_color[3] = a[3];
}

void append_animate_in_ent(void* lhs, const void* rhs_tree) {
	TREE* lhs_tree = ((ENTITY*)lhs)->animate;
	lhs_tree = tree_insert(lhs_tree, rhs_tree);
}

void adapt_each_f_ent ( void* f_in_e, int i, void* msger ) {
	MOMENTUM result = MOMENTUM_INIT;
	static double timer = 0;
	
	if(i == 0)
		timer = glfwGetTime();
	
	result = output_force( f_in_e, timer );
	
	if ( result.angle != 0 ) {
		*(((MOMENTUM_PTR*)msger)->angle) += result.angle;
	}
	else {
		// ! TODO : search surround area object -> compare with them
		
		// ! TODO : on ground -> activate
		// ! TODO : if this object allow phy -> activate
		// ! TODO : apply contextual constant

		if( !(((FORCE*)f_in_e)->identify & (__F_NON_FRICTION__)) |
			(((FORCE*)f_in_e)->identify & (__F_BRAKE__)))
			friction ( f_in_e, &__BASIC_FIRCTION_CONSTANT );
		// ! TODO : Update gravity
		
		vec2_add_assn (
			((MOMENTUM_PTR*)msger)->vector,
			&result.vector
		);
	}
}

void adapt_f_ent ( ENTITY* ent ) {
	MOMENTUM_PTR info_msger = { &(ent->position), &(ent->angle) };
	
	dyn_arr_foreach ( &ent->forces, &ent->position, adapt_each_f_ent );
}

MOMENTUM pass_by_f_ent ( ENTITY* ent) {
	MOMENTUM result = MOMENTUM_INIT;
	MOMENTUM_PTR msger = { &result.vector, &result.angle};
	
	dyn_arr_foreach ( &ent->forces, &msger, adapt_each_f_ent );

	return result;
}

// ! TODO : Modify -> summative entity ( entities that except center )
void draw_ent ( const ENTITY* ent ) {
	if(ent->graphics_buf == NULL)
		return;
	
	mat4 model = GLM_MAT4_IDENTITY_INIT;
	mat4 mvp = GLM_MAT4_IDENTITY_INIT;

	glm_translate_to(
		(mat4)GLM_MAT4_IDENTITY_INIT,
		(vec3) {
			ent->position.x,
			ent->position.y,
			ent->buf_z
		},
		model
	);
	
	gl_get_mvp(model, mvp);

	glm_rotate(mvp, glm_rad(ent->angle), (vec3){0.0f, 0.0f, 1.0f});
	
	// ! TODO : for test code
	gl_draw_sprite_obj ( ent->graphics_buf, *mvp, &ent->texture_pos, &ent->blend_color );
}

void fixed_draw_ent(const ENTITY* ent) {
	if (ent->graphics_buf == NULL)
		return;

	mat4 model = GLM_MAT4_IDENTITY_INIT;
	mat4 mvp = GLM_MAT4_IDENTITY_INIT;

	glm_translate_to(
		(mat4)GLM_MAT4_IDENTITY_INIT,
		(vec3) {
			ent->position.x,
			ent->position.y,
			ent->buf_z
		},
		model
	);

	gl_get_fixed_mvp(model, mvp);

	gl_draw_sprite_obj(ent->graphics_buf, *mvp, &ent->texture_pos, &ent->blend_color);
}

void set_essential_f_ent ( ENTITY* ent ) {
	FORCE inserter = { 0 };
	init_force(&inserter);
	
	if ( ent->forces.capacity < __N_ESSENTAL_FORCE )
		dyn_arr_resize( &ent->forces, __N_ESSENTAL_FORCE );
	
	// !TODO : modify
	if ( (ent->forces).size < __N_ESSENTAL_FORCE )
		ent->forces.size = 1;
		//ent->forces.size = __N_ESSENTAL_FORCE;
	
	// -- CONTROL FORCES ------------
	
	// normal control force
	inserter.identify = __F_FOR_CONTROL__;
	
	dyn_arr_insert( &ent->forces,
				    __I_ESSENTIAL_FORCE__CONTROL + 0,
				    &inserter,
				    copy_force);
	
	// rotate control force
	init_force(&inserter);
	inserter.identify = __F_ROTATE__ | __F_FOR_CONTROL__;
	
	FORCE* test = dyn_arr_insert( &ent->forces,
					__I_ESSENTIAL_FORCE__CONTROL + 1,
					&inserter,
					copy_force);
	
	// -- PHY FORCES ----------------
	//init_force(&inserter);
	
	// !TODO : MODIFY
	//transform_to_gravity ( &inserter, &__EARTH_GRAVITY_CONSTANT, &D_V2_DOWN );
	
	//dyn_arr_insert( &ent->forces, 1, &inserter, copy_force);
	// ------------------------------
}

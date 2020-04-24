#include "user.h"	

void user_walking(_DIRCTION_ direction) {
	VEC2 speed_vec;

	switch (direction) {
	
	case D_N_LEFT:
		speed_vec = vec2_mul(&D_V2_LEFT, g_normal_walk_speed);
		vec2_add_assn(
			g_user_obj->direction_force,
			&speed_vec
		);

		break;

	case D_N_RIGHT:
		speed_vec = vec2_mul(&D_V2_RIGHT, g_normal_walk_speed);
		vec2_add_assn(
			g_user_obj->direction_force,
			&speed_vec
		);

		break;
	}
}
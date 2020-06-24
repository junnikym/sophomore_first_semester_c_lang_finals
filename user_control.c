#include "user_control.h"

void set_control_key(int* which_key, int key_value) {
	*which_key = key_value;
}


void game_control(const int* key, const int* key_act) {
	VEC2 msger = { 0, 0 };
	int identify = __F_FOR_CONTROL__ | __F_NON_FRICTION__;
	double obj_angle = 0.0;
	
	static int left_key_buf = 0;
	static int right_key_buf = 0;
	
	static int foward_key_buf = 0;
	static int back_key_buf = 0;
	
	// ! TODO : change if-else -> switch() {}

	/* ---------------------------------------------------------------------- *
	 * 	KEY PRESSED
	 * ---------------------------------------------------------------------- */
	if (*key_act == __KEY_PRESS) {

		if (*key == __INVENTRY_KEY) {
			toggle_inventory();
		}
		
		/* ----- Direction Key	--------------------------------------------- */
		
		if (*key == __LEFT_KEY) {
			// walk left
			left_key_buf = 1;
			
			direction_buf = -1;
		}

		if (*key == __RIGHT_KEY) {
			// walk right
			right_key_buf = 1;
			
			direction_buf = 1;
			
		}
		
		/* ------------------------------------------------------------------ */
		
		/* ----- Jump 		------------------------------------------------- */
		
		if (*key == __JUMP_KEY) {
			jump_key_buf = 1;
		}

		/* ------------------------------------------------------------------ */
		
		/* ----- Space Control 		----------------------------------------- */
		else {
			if (*key == __FOWARD_KEY) {
				foward_key_buf = 1;
				
				space_thrust_buf = 1;
			}
			
			if (*key == __BACK_KEY) {
				back_key_buf = 1;
				
				space_thrust_buf = -1;
			}
		}
		/* ------------------------------------------------------------------ */
		
	}
	
	/* ---------------------------------------------------------------------- *
	* 	KEY RELEASED
	* ---------------------------------------------------------------------- */
	
	if (*key_act == __KEY_RELEASE) {
		
		/* ----- Direction Key	--------------------------------------------- */
		
		if (*key == __LEFT_KEY) {
			left_key_buf = 0;

			if (right_key_buf == 1) {
				direction_buf = 1;
			}
			else {
				direction_buf = 0;
			}
		}
		
		if (*key == __RIGHT_KEY) {
			right_key_buf = 0;

			if (left_key_buf == 1) {
				direction_buf = -1;
			}
			else {
				direction_buf = 0;
			}
		}
		
		/* ------------------------------------------------------------------ */
		
		/* ----- Jump 		------------------------------------------------- */
		if (*key == __JUMP_KEY) {
			jump_key_buf = 0;
		}

		/* ------------------------------------------------------------------ */
		/* ----- Space Control 		----------------------------------------- */
		else {
			if (*key == __FOWARD_KEY) {
				foward_key_buf = 0;

				if (back_key_buf == 1) {
					space_thrust_buf = -1;
				}
				else {
					space_thrust_buf = 0;
				}
			}
			
			if (*key == __BACK_KEY) {
				back_key_buf = 0;

				if (foward_key_buf == 1) {
					space_thrust_buf = 1;
				}
				else {
					space_thrust_buf = 0;
				}
			}
		}
		/* ------------------------------------------------------------------ */
	}
	
	// -- On the ground
	if ( /* on the ground */ 0) {
		if ( direction_buf != 0) {
			msger.x = direction_buf * direction_buf;
		}
		
		if (jump_time_start != __NOT_ACT_TIME_CODE) {
			msger.y = g_User_Jump;
		}
		
		g_obj_alter ( __FORCE__, &msger, set_accel_in_f,
					  __CENTER_I, __CENTER_I, __I_ESSENTIAL_FORCE__CONTROL );
		
		g_obj_alter ( __FORCE__, &identify, set_identify_in_f,
					  __CENTER_I, __CENTER_I, __I_ESSENTIAL_FORCE__CONTROL );
	}
	// -- Not On the gournd
	else {
		if ( direction_buf != 0) {
			msger.x = g_User_Rotate_Speed * -direction_buf;
		}
		
		g_obj_alter ( __FORCE__, &msger, set_accel_in_f,
			__CENTER_I, __CENTER_I, __I_ESSENTIAL_FORCE__CONTROL + 1 );
		
		msger.x = 0; msger.y = 0;
		
		obj_angle = deg_to_rad( g_obj_get_angle(-1) );
		msger.x = cos(obj_angle);	msger.y = sin(obj_angle);
		
		vec2_mul_assn( &msger, space_thrust_buf * g_User_thrust_Speed);
		
		g_obj_alter ( __FORCE__, &msger, set_accel_in_f,
					  __CENTER_I, __CENTER_I, __I_ESSENTIAL_FORCE__CONTROL );
		
		g_obj_alter ( __FORCE__, &identify, set_identify_in_f,
					  __CENTER_I, __CENTER_I, __I_ESSENTIAL_FORCE__CONTROL );

		g_obj_alter(__ENTITY__, &jump_key_buf, ent_toggle_brake, __CENTER_I, __CENTER_I);
	}

}

void game_control_non_callback() {
	
}

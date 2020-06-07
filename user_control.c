#include "user_control.h"

void set_control_key(int* which_key, int key_value) {
	*which_key = key_value;
}


void game_control(const int* key, const int* key_act) {
	static int left_key_buf = 0;
	static int right_key_buf = 0;
	
	// ! TODO : change if-else -> switch() {}

	/* ---------------------------------------------------------------------- *
	 * 	KEY PRESSED
	 * ---------------------------------------------------------------------- */
	if (*key_act == __KEY_PRESS) {
		
		/* ----- Direction Key	--------------------------------------------- */
		
		if (*key == __LEFT_KEY) {
			// walk left
			left_key_buf = 1;
			direction_buf = -g_User_Speed;
		}

		if (*key == __RIGHT_KEY) {
			// walk right
			right_key_buf = 1;
			direction_buf = g_User_Speed;
		}
		
		/* ------------------------------------------------------------------ */
		
		/* ----- Jump 		------------------------------------------------- */
		
		if (*key == __LONG_JUMP_KEY) {
			if( jump_time_start != 0 )
				long_jump_key_buf = 2;	// fully clked
		}
		
		if (*key == __JUMP_KEY) {
			jump_time_start = glfwGetTime();
			
			if( long_jump_key_buf != 2) {
				
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
				direction_buf = g_User_Speed;
			}
			else {
				direction_buf = 0;
			}
		}
		
		if (*key == __RIGHT_KEY) {
			right_key_buf = 0;

			if (left_key_buf == 1) {
				direction_buf = -g_User_Speed;
			}
			else {
				direction_buf = 0;
			}
		}
		
		/* ------------------------------------------------------------------ */
		
		/* ----- Jump 		------------------------------------------------- */
		
		if (*key == __LONG_JUMP_KEY) {
			long_jump_key_buf = 1;
			// not clked ( if jump key is clkedsd than alter buf to 0 )
		}
		
		if (*key == __JUMP_KEY) {
			if ( long_jump_key_buf == 0 ) {
				jump_time_start = __NOT_ACT_TIME_CODE;
				jump_time_current = __NOT_ACT_TIME_CODE;
			}
		}
		
		/* ------------------------------------------------------------------ */
	}
}

void game_control_non_callback() {
	FORCE msger = { 0 };
	init_force(&msger);
	
	msger.identify = __F_FOR_CONTROL__;
	
	msger.force_vec.x += direction_buf;
	
	/* ----- Jump 		------------------------------------------------- */
	
	// -- Normal Jump
	
	if ( jump_time_start != __NOT_ACT_TIME_CODE ) {
		jump_time_current = glfwGetTime() - jump_time_start;
		
		if( jump_time_current >= __JUMP_DURATION_TIME ) {
			// ! TODO : APPEND THIS CODE
			//
			// if ( is_entity_on_grond() ) {
			//	jump_time_start = glfwGetTime();
			// }
		}
		else {
			msger.force_vec.y = g_User_Jump;
		}
	}
	
	// -- Long Jump
	
	/* ------------------------------------------------------------------ */
	
	g_obj_alter ( __FORCE__, &msger, copy_force,
				  __CENTER_I, __CENTER_I, __I_ESSENTIAL_FORCE__CONTROL );
	
}

#include "user_control.h"

// ------------------------------------------------------- //
// ----- Key Setting function	--------------------------

void set_control_key( int* which_key, int key_value ) {
	*which_key = key_value;
}

// ------------------------------------------------------- //

void game_control(const int* key, const int* key_act) {
	// ! TODO : modify 
	FORCE msger = { 0 };
	//converter[__I_ESSENTIAL_FORCE__CONTROL].force_vec.x = g_User_Speed;
	
	static int left_key_buf = 0;
	static int right_key_buf = 0;
	
	// ! TODO : change if-else -> switch() {}
	
	if ( *key_act == __KEY_PRESS ) {

		if ( *key == __LEFT_KEY ) {
			// walk left
			left_key_buf = 1;
			msger.force_vec.x = -g_User_Speed;
		}
		
		if ( *key == __RIGHT_KEY ) {
			// walk right
			right_key_buf = 1;
			msger.force_vec.x = g_User_Speed;
		}
		
		g_obj_alter( __FORCE__, &msger, g_user_obj_i, -1, __I_ESSENTIAL_FORCE__CONTROL );
	}
	
	if ( *key_act == __KEY_RELESE ) {

		if ( *key == __LEFT_KEY ) {
			left_key_buf = 0;
			
			if(right_key_buf == 1) {
				msger.force_vec.x = g_User_Speed;
			}
			else {
				msger.force_vec.x = 0;
			}
		}
		if ( *key == __RIGHT_KEY ) {
			right_key_buf = 0;
			
			if(left_key_buf == 1) {
				msger.force_vec.x = -g_User_Speed;
			}
			else {
				msger.force_vec.x = 0;
			}
		}
		
		g_obj_alter( __FORCE__, &msger, g_user_obj_i, -1, __I_ESSENTIAL_FORCE__CONTROL );
	}

	if ( *key == __JUMP_KEY && *key_act == __KEY_RELESE) {
		// preliminary motion 
	}
	else if ( *key == __JUMP_KEY && *key_act == __KEY_RELESE) {
		// Jump
	}
}

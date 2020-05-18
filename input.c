#include "input.h"

extern OBJECT g_user_obj;

// ------------------------------------------------------- //
// ----- Key Setting function	--------------------------

void set_control_key( int* which_key, int key_value ) {
	*which_key = key_value;
}

// ------------------------------------------------------- //

void game_control(const int* key, const int* key_act) {
	FORCE* converter = g_user_obj.center->forces.items;
	
	// ! TODO : change if-else -> switch() {}
	
	if ( *key_act == __KEY_PRESS ) {

		if ( *key == __LEFT_KEY ) {
			// walk left
			g_left_key_buf = 1;
			converter[__I_ESSENTIAL_FORCE__CONTROL].force_vec.x = -0.01;
		}
		
		if ( *key == __RIGHT_KEY ) {
			// walk right
			g_right_key_buf = 1;
			converter[__I_ESSENTIAL_FORCE__CONTROL].force_vec.x = 0.01;
		}
		
	}
	
	if ( *key_act == __KEY_RELESE ) {

		if ( *key == __LEFT_KEY ) {
			g_left_key_buf = 0;
			
			if(g_right_key_buf == 1) {
				converter[__I_ESSENTIAL_FORCE__CONTROL].force_vec.x = 0.01;
			}
			else {
				converter[__I_ESSENTIAL_FORCE__CONTROL].force_vec.x = 0;
			}
		}
		if ( *key == __RIGHT_KEY ) {
			g_right_key_buf = 0;
			
			if(g_left_key_buf == 1) {
				converter[__I_ESSENTIAL_FORCE__CONTROL].force_vec.x = -0.01;
			}
			else {
				converter[__I_ESSENTIAL_FORCE__CONTROL].force_vec.x = 0;
			}
		}
		
	}

	if ( *key == __JUMP_KEY && *key_act == __KEY_RELESE) {
		// preliminary motion 
	}
	else if ( *key == __JUMP_KEY && *key_act == __KEY_RELESE) {
		// Jump
	}
}

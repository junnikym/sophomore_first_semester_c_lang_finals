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
			converter[0].identify &= ~(F_PAUSE);
		}
		
		if ( *key == __RIGHT_KEY ) {
			// walk right
			converter[1].identify &= ~(F_PAUSE);
		}
		
	}
	
	if ( *key_act == __KEY_RELESE ) {

		if ( *key == __LEFT_KEY ) {
			converter[0].identify |= F_PAUSE;
		}
		
		if ( *key == __RIGHT_KEY ) {
			converter[1].identify |= F_PAUSE;
		}
	
	}

	if ( *key == __JUMP_KEY && *key_act == __KEY_RELESE) {
		// preliminary motion 
	}
	else if ( *key == __JUMP_KEY && *key_act == __KEY_RELESE) {
		// Jump
	}
}

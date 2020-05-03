#include "input.h"

// ------------------------------------------------------- //
// ----- Key Setting function	--------------------------

void set_control_key( int* which_key, int key_value ) {
	*which_key = key_value;
}

// ------------------------------------------------------- //

void game_control(const int* key, const int* key_act) {

	if ( key == __LEFT_KEY && key_act == __KEY_PRESS) {	// RIGHT
		// walk right
	}
	if (key == __RIGHT_KEY && key_act == __KEY_PRESS) {	// LEFT
		// walk left
	}

	if (key == __JUMP_KEY && key_act == __KEY_RELESE) {
		// preliminary motion 
	}
	else if (key == __JUMP_KEY && key_act == __KEY_RELESE) {
		// Jump
	}
}
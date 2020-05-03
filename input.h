#ifndef INPUT_H
#define INPUT_H

#include "types.h"

// -- Control Keys

static int __LEFT_KEY = 0;
static int __RIGHT_KEY = 0;
static int __JUMP_KEY = 0;

static int __KEY_PRESS = 0;
static int __KEY_RELESE = 0;

// ------------------------------------------------------- //
// ----- Key Setting function	--------------------------

void set_control_key( int* which_key, int key_value );

// ------------------------------------------------------- //

void game_control(const int* key, const int* key_act);

#endif
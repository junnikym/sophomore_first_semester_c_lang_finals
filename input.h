#ifndef INPUT_H
#define INPUT_H

#include "types.h"
#include "memory.h"
#include "entity.h"

// -- Control Keys

static int __LEFT_KEY = GLFW_KEY_LEFT;
static int __RIGHT_KEY = GLFW_KEY_RIGHT;
static int __JUMP_KEY = 0;

static int __KEY_PRESS = GLFW_PRESS;
static int __KEY_RELESE = GLFW_RELEASE;\

static int g_left_key_buf = 0;
static int g_right_key_buf = 0;

// ------------------------------------------------------- //
// ----- Key Setting function	--------------------------

void set_control_key( int* which_key, int key_value );

// ------------------------------------------------------- //

void game_control(const int* key, const int* key_act);

#endif

#ifndef USER_CONTROL_H
#define USER_CONTROL_H

#include "vector2.h"
#include "memory.h"
#include "entity.h"

// -- Values for Control

static int g_User_Speed = 1;

// -- Control Keys

static int __LEFT_KEY = GLFW_KEY_LEFT;
static int __RIGHT_KEY = GLFW_KEY_RIGHT;
static int __JUMP_KEY = 0;

static int __KEY_PRESS = GLFW_PRESS;
static int __KEY_RELESE = GLFW_RELEASE;

// ------------------------------------------------------- //
// ----- Key Setting function		----------------------

void set_control_key( int* which_key, int key_value );

// ------------------------------------------------------- //

void game_control(const int* key, const int* key_act);

#endif

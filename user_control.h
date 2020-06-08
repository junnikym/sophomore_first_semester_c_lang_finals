#ifndef USER_CONTROL_H
#define USER_CONTROL_H

#include "vector2.h"
#include "memory.h"
#include "entity.h"

// -- Values for Control

#define __NOT_ACT_TIME_CODE -1

#define __JUMP_STRENGHT 1
#define __LONG_JUMP_STRENGHT 2

#define __JUMP_COOL_DOWN_TIME 1
#define __JUMP_DURATION_TIME 1

static int g_User_Speed = 5;
static int g_User_Jump = 5;
static int g_User_Long_Jump = 2;

static double direction_buf = 0.0;

static int long_jump_key_buf = 0;
static double long_jump_time = __NOT_ACT_TIME_CODE;

static double jump_time_start = __NOT_ACT_TIME_CODE;
static double jump_time_current = __NOT_ACT_TIME_CODE;

// -- Control Keys

static int __LEFT_KEY = GLFW_KEY_A;			// LEFT?		'A'
static int __RIGHT_KEY = GLFW_KEY_D;		// RIHGT	?	'D'
static int __JUMP_KEY = GLFW_KEY_SPACE;		// JUMP				'SPACE'
static int __LONG_JUMP_KEY = GLFW_KEY_W;	// LONG_JUMP		'W'
static int __TAB_KEY = GLFW_KEY_TAB;		// INVENTORY		'TAB'
static int __E_KEY = GLFW_KEY_E;			// INTERACTOIN		'E'
static int __ESC_KEY = GLFW_KEY_ESCAPE;		// MENU ( IN GAME)	'ESC'

static int __NUM1_KEY = GLFW_KEY_1;			// ITEM 1			'1'
static int __NUM2_KEY = GLFW_KEY_2;			// ITEM 2			'2'
static int __NUM3_KEY = GLFW_KEY_3;			// ITEM 3			'3'

static int __KEY_PRESS = GLFW_PRESS;
static int __KEY_RELEASE = GLFW_RELEASE;

// ------------------------------------------------------- //
// ----- Key Setting function		----------------------

void set_control_key( int* which_key, int key_value );

// ------------------------------------------------------- //
// ----- Control function			----------------------

void game_control(const int* key, const int* key_act);
void game_control_non_callback();


#endif

#ifndef PRESS_ANY_KEY_H
#define PRESS_ANY_KEY_H

#include "../opengl/system.h"
#include "../opengl/buffer_obj.h"
#include "../opengl/control.h"
#include "../opengl/callback.h"

#include "../vector2.h"
#include "../memory.h"

#define __HEART_SIZE 5
#define __HEART_INTERVAL 12.5
#define __DIST_BETWEEN_H_E 15.0		// distance between heart and energy

static const VEC2 __HEART_WHERE = { -230, 160 };

INPUT_COMPONANT g_input;

static ENTITY g_HEART;
static ENTITY g_ENERGY;

typedef enum __SCREEN_CODE__ {
	__MAIN_SCREEN = 0,
	__NEW_GAME_SCREEN = 1,
	__OPTION_SCREEN = 2,
	__COUNTINUE = 3,
	__EXIT = 4
} _SCREEN_CODE_;

static double loaded_time = 0.0;

void reset_loaded_time();

void title_test( );
void title_img_load();

void main_screen();
void main_screen_load();

void init_game();
void init_indicator();
void info_indicator(const VEC2* cam_pos, int hearts, int energy);

void tutorial_text();
void new_game();
void new_game_load();

#endif
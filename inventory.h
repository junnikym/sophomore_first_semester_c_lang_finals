#ifndef PRESS_ANY_KEY_H
#define PRESS_ANY_KEY_H

#include <memory.h>

#include "opengl/system.h"
#include "opengl/buffer_obj.h"
#include "opengl/control.h"
#include "opengl/callback.h"

#include "vector2.h"
#include "memory.h"

INPUT_COMPONANT g_input;

typedef enum __SCREEN_CODE__ {
	__MAIN_SCREEN = 0,
	__NEW_GAME_SCREEN = 1,
	__OPTION_SCREEN = 2,
	__COUNTINUE = 3,
	__EXIT = 4
} _SCREEN_CODE_;

void inventory_test();
void inventory_img_load();
void inventory_state();

#endif
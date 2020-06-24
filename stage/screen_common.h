#ifndef SCREEN_COMMON_H
#define SCREEN_COMMON_H

#include "../opengl/control.h"

#include "press_any_key.h"

static void (*current_screen)( ) = NULL;

void init_screen();							// 화면 초기화

void transe_screen (int screen_code );		// 스크린 코드로 통해 화면 전환

void run_current_screen();					// 화면 시작

#endif

#ifndef SCREEN_FORM_H
#define SCREEN_FORM_H

#include <stdarg.h>

#include "entity.h"
#include "opengl/callback.h"

#define __CREAT_SCREEN_CODE 1
#define __RELEASE_SCREEN_CODE -1

/* 현재 화면을 표시할 함수를 가르키는 포인터
*	공통 인자 순서
*	1. 실행 코드
*/
static void (*current_screen) (int args, ...);

// ------------------------------------------------------- //
// ----- Screen Attribute	------------------------------

void convert_screen(void (*screen)(int args, ...));

// -- game start screen
void intro_screen();
void new_game_screen(int args, ...);
void menu_screen(int args, ...);
void setting_screen(int args, ...);
void info_screen(int args, ...);

// -- in game screen
void in_game_screen(int args, ...);

void in_game_menu_screen();
void in_game_setting_menu();

// ------------------------------------------------------- //

#endif
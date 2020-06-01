#include "screen_form.h"

void convert_screen(void (*screen)(const int* args, ...)) {
	current_screen(-1);
	current_screen = screen;
}

void intro_screen() {

}

/* menu_screen : 가변 인자 목록
* 
* 1. const int* key, 
* 2. const int* key_act, 
* 3. const MOUSE_INPUT* mouse_info
*/
void menu_screen	( int exec_code, ... ) {	
	/* 사용자로부터 어떤 메뉴를 선택 받음 */
	static ENTITY* attr = NULL;
	static const int n_attr = 5;

	va_list ap;

	const int* key = NULL;
	const int* key_act = NULL;
	const MOUSE_INPUT* mouse_info = NULL;

	/*	메뉴 구성
	*	0. 타이틀
	*	1. 새로운 시작
	*	2. 계속하기
	*	3. 설정
	*	4. 종료
	*/

	if (exec_code == __CREAT_SCREEN_CODE) {
		attr = (ENTITY*)malloc(sizeof(ENTITY) * n_attr);

		init_ent(&attr[0]);
		/*
		graphics_buf = title;
		attr[0].position = (left top position);
		attr[0].size = (right bottom position);
		
		... -> [1]... [2]...
		*/
	}

	else if (exec_code == __RELEASE_SCREEN_CODE) {
		free(attr);
		attr = NULL;
		return;
	}

	else {
		if (attr = NULL) // ERROR 발생 시
			return;
	}

	va_start(ap, exec_code);

	key = va_arg(ap, const int*);
	key_act = va_arg(ap, const int*);
	mouse_info = va_arg(ap, const MOUSE_INPUT*);
	
	if (mouse_info->cur.x > /* attr[1].position.x */ && 
		mouse_info.cur->x < /* attr[1].size.x */ &&
		mouse_info->cur.y < /* attr[1].position.y */ && 
		mouse_info.cur->y > /* attr[1].size.y */) {

		convert_screen(new_game_screen);
	}
	else if (mouse_info->cur.x > /* attr[2].position.x */&&
			 mouse_info.cur->x < /* attr[2].size.x */&&
			 mouse_info->cur.y < /* attr[2].position.y */&&
			 mouse_info.cur->y > /* attr[2].size.y */) {
		convert_screen(menu_screen);
	}
	/* ... */


}
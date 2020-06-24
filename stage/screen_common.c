#include "screen_common.h"

void init_screen() {				//초기화 함수
	title_img_load();				// 이미지 로드
	current_screen = title_test;	// 화면을 현재 화면에 넣어준다.
}

void transe_screen(int screen_code ) {
	// 화면 전환을 담당하는 함수.
	// 스크린 코드를 이용해 다음 화면으로 넘어간다.
	// 1. 메인화면 시작
	// 2. 새로운 게임
	// 3. 옵션
	// 4. 종료

	g_obj_release();	// 해제
	g_obj_init();		// 초기화

	switch (screen_code) {

	case __MAIN_SCREEN:			 //Main_screen
		main_screen_load();
		current_screen = main_screen;

		break;

	case __NEW_GAME_SCREEN:		//New_game
	
		
		break;
			
	case 3:						//Option
		//Option();

	case 4:						//Exit
		exit(1);

	default:
		printf("ERROR \n");
	}
}

void run_current_screen() {		// 현재 화면 시작 함수
	current_screen();			// 현재 화면 시작
}
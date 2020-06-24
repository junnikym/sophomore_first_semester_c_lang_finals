#include "screen_common.h"

void init_screen() {				//�ʱ�ȭ �Լ�
	init_game();
	reset_loaded_time();
	title_img_load();				// �̹��� �ε�
	current_screen = title_test;	// ȭ���� ���� ȭ�鿡 �־��ش�.
}

void transe_screen(int screen_code ) {
	// ȭ�� ��ȯ�� ����ϴ� �Լ�.
	// ��ũ�� �ڵ带 �̿��� ���� ȭ������ �Ѿ��.
	// 1. ����ȭ�� ����
	// 2. ���ο� ����
	// 3. �ɼ�
	// 4. ����

	reset_loaded_time();
	g_obj_release();	// ����
	g_obj_init();		// �ʱ�ȭ

	switch (screen_code) {

	case __MAIN_SCREEN:			 //Main_screen
		main_screen_load();
		current_screen = main_screen;

		break;

	case __NEW_GAME_SCREEN:		//New_game
		init_game();
		new_game_load();
		current_screen = new_game;
	
		break;

	case __COUNTINUE:		// countinue
		init_game();

		break;
			
	case __OPTION_SCREEN:		//Option

		break;

	case __EXIT:						//Exit
		exit(1);

	default:
		printf("ERROR \n");
	}
}

void run_current_screen() {		// ���� ȭ�� ���� �Լ�
	current_screen();			// ���� ȭ�� ����
}
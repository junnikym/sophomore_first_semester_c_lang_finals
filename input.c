#include "input.h"

void game_control(const int* key, const int* key_act) {
	// ! TODO : ����� ���������� ������ ��
	// ! TODO : left�� ������ �ڿ� right ���� -> right ������ : right�� ������ -> left ������ 
	if ( key == GLFW_KEY_D && key_act == GLFW_PRESS) {	// RIGHT
		user_walking(D_N_RIGHT);
	}
	if (key == GLFW_KEY_A && key_act == GLFW_PRESS) {	// LEFT
		user_walking(D_N_LEFT);
	}

	// ! TODO : ����Ű�� ���� �� -> ���� �غ�; ����Ű�� ���ȴ� ���� �� -> ���� ����;
	if (key == GLFW_KEY_A && key_act == GLFW_PRESS) {
		// preliminary motion 
	}
	else if (key == GLFW_KEY_A && key_act == GLFW_RELEASE) {
		// Jump
	}
}
#include "input.h"

void game_control(const int* key, const int* key_act) {
	// ! TODO : ����� ���������� ������ ��
	// ! TODO : left�� ������ �ڿ� right ���� -> right ������ : right�� ������ -> left ������ 
	if ( key == GLFW_KEY_D && key_act == GLFW_PRESS) {
		// right accel
	}
	if (key == GLFW_KEY_A && key_act == GLFW_PRESS) {
		// left accel	
	}

	// ! TODO : ����Ű�� ���� �� -> ���� �غ�; ����Ű�� ���ȴ� ���� �� -> ���� ����;
	if (key == GLFW_KEY_A && key_act == GLFW_PRESS) {
		// preliminary motion 
	}
	else if (key == GLFW_KEY_A && key_act == GLFW_RELEASE) {
		// Jump
	}
}
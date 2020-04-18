#include "input.h"

void game_control(const int* key, const int* key_act) {
	// ! TODO : 사용자 지정값으로 변경할 것
	// ! TODO : left가 눌리고 뒤에 right 눌림 -> right 움직임 : right가 때어짐 -> left 움직임 
	if ( key == GLFW_KEY_D && key_act == GLFW_PRESS) {
		// right accel
	}
	if (key == GLFW_KEY_A && key_act == GLFW_PRESS) {
		// left accel	
	}

	// ! TODO : 점프키가 눌릴 시 -> 점프 준비; 점프키가 눌렸다 때질 시 -> 점프 실행;
	if (key == GLFW_KEY_A && key_act == GLFW_PRESS) {
		// preliminary motion 
	}
	else if (key == GLFW_KEY_A && key_act == GLFW_RELEASE) {
		// Jump
	}
}
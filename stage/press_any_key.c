#include "press_any_key.h"
#include "../text.h"
#include "../sound.h"
#include "inventory.h"

void reset_loaded_time() {
	loaded_time = glfwGetTime();
}

void title_img_load() {
	// 처음 화면의 press_any_key.
	int result = 0;

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glColor4f(1, 1, 1, 0.1);

	//이미지의 위치를 잡아준다.
	VEC2 pos0 = (VEC2){ 1, 1 };		// test
	VEC2 pos1 = (VEC2){ 0, -10 };	// press_any_key.

	FORCE test_f_inserter = generate_force((VEC2) { 0, 0 }, __F_ACCELERATE__);
	test_f_inserter.accel_vec = (VEC2){ 0, 1 };

	GLfloat buf_vertice[32] = { 0 };

	BUFFER_ATTRIBUTES buf_obj_attr = {
		buf_vertice,
		sizeof(buf_vertice),
		g_SQUARE_INDICES,
		sizeof(g_SQUARE_INDICES)
	};

	memcpy(buf_vertice, g_SQUARE_VERTICES, sizeof(buf_vertice));

	//-------------------- background

	/*----- OBJECT 0 	------------------------------------------------------------*/
	/* |*/	g_obj_push_thing(__OBJECT__, NULL);
	/* |		-- [0] : ENTITY 0		*/
	/* |*/	g_obj_push_thing(__ENTITY__, NULL, 0);
	/* |*/	g_obj_set_center_ent(0, 0);
	/* |*/	g_obj_set_obj_buf("background", 0, 0);		// set texture
	//g_obj_alter(__ENTITY__, &pos0, modify_ent, 0, 0);
	/*------------------------------------------------------------------------------*/
}

void title_test() {

	if (g_input.key_action == GLFW_PRESS && g_input.key == GLFW_KEY_2) {
		
		PlayEffect(click_event);
	
		transe_screen(__MAIN_SCREEN);		// go to mainscreen
		
	}
	//-------------------- press any key

	if ( (int)((glfwGetTime() - loaded_time)*2) % 2 == 1 ) {
		Text_drew("press any key", -3.0, -5.0, 1.0, 0.2);
	}

}
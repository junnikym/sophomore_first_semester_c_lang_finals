#include "press_any_key.h"
#include "../text.h"
#include "../sound.h"

void main_screen_load() {
	int result = 0;

	VEC2 pos0 = (VEC2){ 0, -3 }; //background
	VEC2 pos1 = (VEC2){ 0, 0 }; //New game button
	VEC2 pos2 = (VEC2){ 0, -5 }; //Continue button
	VEC2 pos3 = (VEC2){ 0, -10 }; //Option button
	VEC2 pos4 = (VEC2){ 0, -15 }; //Exit button

	FORCE test_f_inserter = generate_force((VEC2) { 0, 0 }, __F_ACCELERATE__);
	test_f_inserter.accel_vec = (VEC2){ 0, 1 };

	//Exit button

	/*----- OBJECT 0 	------------------------------------------------------------*/
	/* |*/	g_obj_push_thing(__OBJECT__, NULL);
	/* |		-- [0] : ENTITY 0		*/
	/* |*/	g_obj_push_thing(__ENTITY__, NULL, 0);
	/* |*/	g_obj_set_center_ent(0, 0);
	/* |*/	g_obj_set_obj_buf("background", 0, 0);		// set texture
	g_obj_alter(__ENTITY__, &pos0, modify_ent, 0, 0);
	/*------------------------------------------------------------------------------*/

}

void main_screen() {

	static vec4 blend = { 1.0f,1.0f ,1.0f ,0.0f };
	static double start_t = 0.0;

	if (start_t == 0) {
		start_t = glfwGetTime();
	}

	if (blend[3] < 1.0) {
		blend[3] = glfwGetTime() - start_t;
	}
	else
		blend[3] = 1.0;

	if (g_input.key == GLFW_KEY_1 && g_input.key_action == GLFW_PRESS) {

		PlayEffect(click_event);
		transe_screen(__NEW_GAME_SCREEN);
	}// NEW GAME

	if (g_input.key == GLFW_KEY_2 && g_input.key_action == GLFW_PRESS) {

		PlayEffect(click_event);
		transe_screen(__OPTION_SCREEN);
	}// COUNTINUE

	if (g_input.key == GLFW_KEY_3 && g_input.key_action == GLFW_PRESS) {

		PlayEffect(click_event);
		transe_screen(__COUNTINUE);
	}// OPTION

	if (g_input.key == GLFW_KEY_4 && g_input.key_action == GLFW_PRESS) {

		PlayEffect(click_event);
		transe_screen(__EXIT);
	}// EXIT

	//New game button
	Text_drew("NEW GAME ( KEY 1 )", -3.0, -1.0, 1.0, 0.2);

	//Continue button
	Text_drew("CONTINUE ( KEY 2 )", -3.0, -3.0, 1.0, 0.2);

	//Option button
	Text_drew("OPTION ( KEY 3 )", -3.0, -5.0, 1.0, 0.2);

	//Exit button
	Text_drew("EXIT ( KEY 4 )", -3.0, -7.0, 1.0, 0.2);

	//g_obj_alter(__ENTITY__, blend, set_blend_in_ent, 0, 0);

	update_g_obj ( );
}
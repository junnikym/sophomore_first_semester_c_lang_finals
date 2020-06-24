#include "press_any_key.h"
#include "../sound.h"

void main_screen_load() {
	int result = 0;

	VEC2 pos0 = (VEC2){ 0, 0 }; //background
	VEC2 pos1 = (VEC2){ 0, 0 }; //New game button
	VEC2 pos2 = (VEC2){ 0, -5 }; //Continue button
	VEC2 pos3 = (VEC2){ 0, -10 }; //Option button
	VEC2 pos4 = (VEC2){ 0, -15 }; //Exit button

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

	set_square_vertices(buf_vertice, (VEC2) { 42.0f, -28.0f }, 0.0f, (VEC2) { 1.0f, 1.0f });

	g_buf_obj_insert("background",
		gl_load_BMP("../../resource/texture/background/background_S02.bmp"),
		&buf_obj_attr);

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

	if (g_input.key == GLFW_KEY_1 && g_input.key_action == GLFW_PRESS) {

		PlayEffect(click_event);
		transe_screen(__NEW_GAME_SCREEN);
	}

	//New game button
	Text_drew("NEW GAME", -3.0, -1.0, 1.0, 0.2);

	//Continue button
	Text_drew("CONTINUE", -3.0, -3.0, 1.0, 0.2);

	//Option button
	Text_drew("OPTION", -3.0, -5.0, 1.0, 0.2);

	//Exit button
	Text_drew("EXIT", -3.0, -7.0, 1.0, 0.2);


}
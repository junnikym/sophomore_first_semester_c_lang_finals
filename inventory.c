#include "inventory.h"
#include "text.h"
#include "sound.h"

void inventory_img_load() {

	int result = 0;

	//이미지의 위치를 잡아준다.
	VEC2 pos0 = (VEC2){ 1, 1 };		// test

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

	//-------------------- inventory

	

	/*----- OBJECT 0 	------------------------------------------------------------*/
	/* |*/	g_obj_push_thing(__OBJECT__, NULL);
	/* |		-- [0] : ENTITY 0		*/
	/* |*/	g_obj_push_thing(__ENTITY__, NULL, 1);
	/* |*/	g_obj_set_center_ent(1, 0);
	/* |*/	g_obj_set_obj_buf("inventory", 1, 0);		// set texture
	//g_obj_alter(__ENTITY__, &pos0, modify_ent, 0, 0);
	/*------------------------------------------------------------------------------*/

}


void inventory_test() {

	if (g_input.key_action == GLFW_PRESS && g_input.key == GLFW_KEY_TAB) {

		PlayEffect(click_event);
		inventory_img_load();
	
		Text_drew("tab key!!", -3.0, -10.0, 1.0, 0.2);

	
	}

	if (g_input.key_action == GLFW_RELEASE && g_input.key == GLFW_KEY_TAB) {


		PlayEffect(click_event);

	}
}


void inventory_state() {

}
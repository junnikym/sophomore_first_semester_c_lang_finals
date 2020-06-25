#include "press_any_key.h"
#include "inventory.h"

void init_game() {
	init_inventory();
	init_indicator();
}

void new_game_load() {
	/*----- USER OBJECT	------------------------------------------------------- */

	g_obj_push_thing(__OBJECT__, NULL);

	// -- Entity 0 -- //
	g_obj_push_thing(__ENTITY__, NULL, 0);
	g_obj_set_center_ent(0, 0);
	g_obj_set_essential_f(0, -1);
	g_obj_set_obj_buf("main_character_walk", 0, -1);	// set texture
	g_obj_append_collision_box(0, (BOX) { (VEC2) { 0.0f, 0.0f }, (VEC2) { 2.5f, 2.5f } });
	g_obj_append_interaction_box(0, (BOX) { (VEC2) { 0.0f, 0.0f }, (VEC2) { 2.5f, 2.5f } });

	g_obj_set_user_obj(0);
	g_world_insert_obj(0);

	/*-------------------------------------------------------------------------- */
	/*----- MAIN SHIP	 ------------------------------------------------------- */

	g_obj_push_thing(__OBJECT__, NULL);

	// -- Entity 0 -- //
	g_obj_push_thing(__ENTITY__, NULL, 1);
	g_obj_set_center_ent(1, 0);
	g_obj_set_essential_f(1, -1);
	g_obj_set_obj_buf("ship_b", 1, -1);	// set texture
	g_obj_append_collision_box(0, (BOX) { (VEC2) { 0.0f, 0.0f }, (VEC2) { 2.5f, 2.5f } });
	g_obj_append_interaction_box(0, (BOX) { (VEC2) { 0.0f, 0.0f }, (VEC2) { 2.5f, 2.5f } });

	g_world_insert_obj(1);

	/*-------------------------------------------------------------------------- */
}

void new_game() {
	static int tut_sequence = 0;

	static char* tut_phrase[] = {
		"W, S key : trust front and back ",
		"A , D  key : turn",
		"Space Key : brake",
		"return to your ship"
	};

	VEC2 tut_pos = V2_ZERO;
	VEC2 user_pos = V2_ZERO;
	VEC2 update_section = V2_ZERO;

	int interaction_i[4] = { 0 };

	double tut_range = 0.0;

	if (is_g_user_obj_setted()) {
		game_control_non_callback();	// 유저의 컨트롤을 위한 함수
	}

	user_pos = g_obj_get_position(__CENTER_I);

	// 게임에 사용될 객체들을 모두 업데이트 시켜줌
	update_section = world_where(user_pos);
	g_world_update(update_section.x, update_section.y);

	// 충돌 체크
	g_world_process(update_section.x, update_section.y, interaction_i);

	printf("interaction %d, %d, %d, %d \n",
		interaction_i[0], interaction_i[1], interaction_i[2], interaction_i[3]);

	// 화면에 표시될 뷰를 업데이트된 위치로 적용
	gl_set_view_pos((vec3) { user_pos.x, user_pos.y, g_cam_dist });
	gl_update_cam();

	// ! TODO : modify hearts number
	info_indicator(&user_pos,10, 4);

	tut_range = vec2_get_size(&user_pos);

	if(tut_range > 50*(tut_sequence+1)) {
		tut_pos = user_pos;
		tut_sequence++;
	}

	if (tut_sequence < 3) {
		Text_drew(tut_phrase[tut_sequence], (int)tut_pos.x, (int)tut_pos.y + 5, 1.0f, 0.2f);
	}

	if (is_open_inventory() != 0)
		show_inventory(&user_pos);
}
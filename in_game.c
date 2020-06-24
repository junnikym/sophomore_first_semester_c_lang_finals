#include "in_game.h"

void new_game_init ( ) {

/*----- User Object 	------------------------------------------------------------*/
	g_obj_push_thing ( __OBJECT__, NULL );
	g_obj_set_user_obj ( 0 );
	
	// -- Entity 0 -- //
	g_obj_push_thing ( __ENTITY__, NULL, 0 );
	g_obj_set_center_ent ( 0, 0 );
	g_obj_set_essential_f ( 0, -1 );
	g_obj_set_obj_buf ( "main_character_walk", 0, -1 );	// set texture
	g_obj_append_collision_box ( 0, (BOX) { (VEC2) { 0.0f, 0.0f }, (VEC2) { 2.5f, 2.5f } } );

	g_obj_set_user_obj(-1);
/*----------------------------------------------------------------------------------*/

}

void in_game_run ( ) {
	VEC2 user_pos = V2_ZERO;
	VEC2 update_section = V2_ZERO;

	if ( is_g_user_obj_setted ( ) ) {
		game_control_non_callback ( );	// ������ ��Ʈ���� ���� �Լ�
	}

	user_pos = g_obj_get_position ( __CENTER_I );

	// ���ӿ� ���� ��ü���� ��� ������Ʈ ������
	update_section = world_where ( user_pos );
	g_world_update ( update_section.x, update_section.y );

	// �浹 üũ
	g_world_collsion_process ( update_section.x, update_section.y );

	// ȭ�鿡 ǥ�õ� �並 ������Ʈ�� ��ġ�� ����
	gl_set_view_pos ( (vec3) { user_pos.x, user_pos.y, g_cam_dist } );
	gl_update_cam ( );

}
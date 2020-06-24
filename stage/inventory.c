#include "inventory.h"

void toggle_inventory() {
	if (open_inventory == 0) {
		open_inventory = 1;
	}
	else {
		open_inventory = 0;
	}

	printf("is open ? : %d \n", open_inventory);
}

int is_open_inventory() {
	return open_inventory;
}

void init_inventory() {

	BUFFER_OBJECT* buf_obj = NULL;
	GLfloat buf_vertice[32] = { 0 };

	BUFFER_ATTRIBUTES buf_obj_attr = {
	   buf_vertice,
	   sizeof(buf_vertice),
	   g_SQUARE_INDICES,
	   sizeof(g_SQUARE_INDICES)
	};

	ENTITY inserter;

	init_obj(&g_INVENTORY);

	// ----- INVENTORY BACKGROUND

	init_ent(&inserter);
	set_square_vertices(buf_vertice, (VEC2) { 125, 80 }, 0.0f, (VEC2) { 1.0f, 1.0f });

	inserter.buf_z = 75.0;		// 다른 물체에 가려짐을 방지하여 z값을 놓게 설정

	buf_obj = (BUFFER_OBJECT*)malloc(sizeof(BUFFER_OBJECT));
	buf_obj_init(buf_obj);

	buf_obj->ID = g_shader_id;
	buf_obj->texture = gl_load_DDS("../../resource/texture/item/inventory_bg.dds");;
	buf_obj->n = __BUFFER_GEN_N;

	gl_define_buf_obj(buf_obj, &buf_obj_attr, buf_obj->n);
	gl_define_texture(&buf_obj->ID, &buf_obj->texture, 0);
	inserter.graphics_buf = buf_obj;

	dyn_arr_push_back(&g_INVENTORY.entities, &inserter, copy_ent);
	buf_obj = NULL;

	set_center_obj(&g_INVENTORY, 0);

	// ----- INVENTORY GRID

	init_ent(&inserter);
	set_square_vertices(buf_vertice, (VEC2) { 65, 65 }, 1.0f, (VEC2) { 1.0f, 1.0f });

	inserter.position = (VEC2){ 45.0, 0.0 };
	inserter.buf_z = 75.1;

	buf_obj = (BUFFER_OBJECT*)malloc(sizeof(BUFFER_OBJECT));
	buf_obj_init(buf_obj);

	buf_obj->ID = g_shader_id;
	buf_obj->texture = gl_load_DDS("../../resource/texture/item/inventory.dds");;
	buf_obj->n = __BUFFER_GEN_N;

	gl_define_buf_obj(buf_obj, &buf_obj_attr, buf_obj->n);
	gl_define_texture(&buf_obj->ID, &buf_obj->texture, 0);
	inserter.graphics_buf = buf_obj;

	dyn_arr_push_back(&g_INVENTORY.entities, &inserter, copy_ent);
	buf_obj = NULL;

	// ----- INVENTORY CHARACTER IMG

	init_ent(&inserter);
	set_square_vertices(buf_vertice, (VEC2) { 35, 35 }, 1.0f, (VEC2) { 0.0625, 1.0 });

	inserter.position = (VEC2){ -65, 0.0 };
	inserter.buf_z = 75.2;

	buf_obj = (BUFFER_OBJECT*)malloc(sizeof(BUFFER_OBJECT));
	buf_obj_init(buf_obj);

	buf_obj->ID = g_shader_id;
	buf_obj->texture = gl_load_DDS("../../resource/texture/character/player_walk_sprite.dds");;
	buf_obj->n = __BUFFER_GEN_N;

	gl_define_buf_obj(buf_obj, &buf_obj_attr, buf_obj->n);
	gl_define_texture(&buf_obj->ID, &buf_obj->texture, 0);
	inserter.graphics_buf = buf_obj;

	dyn_arr_push_back(&g_INVENTORY.entities, &inserter, copy_ent);
	buf_obj = NULL;
}

void show_inventory(const VEC2* cam_pos) {
	g_INVENTORY.center->position = *cam_pos;

	draw_obj(&g_INVENTORY, 1);
}
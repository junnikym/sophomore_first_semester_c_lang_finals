#include "press_any_key.h"

void init_indicator() {
	init_ent(&g_HEART);
	init_ent(&g_ENERGY);

	BUFFER_OBJECT* buf_obj_h = NULL;
	BUFFER_OBJECT* buf_obj_e = NULL;
	GLfloat buf_vertice[32] = { 0 };

	BUFFER_ATTRIBUTES buf_obj_attr = {
	   buf_vertice,
	   sizeof(buf_vertice),
	   g_SQUARE_INDICES,
	   sizeof(g_SQUARE_INDICES)
	};

	set_square_vertices(buf_vertice, (VEC2) { __HEART_SIZE, __HEART_SIZE }, 1.0f, (VEC2) { 1.0f, 1.0f });

	// ----- HEART

	buf_obj_h = (BUFFER_OBJECT*)malloc(sizeof(BUFFER_OBJECT));
	buf_obj_init(buf_obj_h);

	buf_obj_h->ID = g_shader_id;
	buf_obj_h->texture = gl_load_DDS("../../resource/texture/Stack/heart.dds");;
	buf_obj_h->n = __BUFFER_GEN_N;

	gl_define_buf_obj(buf_obj_h, &buf_obj_attr, buf_obj_h->n);

	gl_define_texture(&buf_obj_h->ID, &buf_obj_h->texture, 0);

	g_HEART.graphics_buf = buf_obj_h;

	// ----- ENERGY
	
	buf_obj_e = (BUFFER_OBJECT*)malloc(sizeof(BUFFER_OBJECT));
	buf_obj_init(buf_obj_e);

	buf_obj_e->ID = g_shader_id;
	buf_obj_e->texture = gl_load_DDS("../../resource/texture/Stack/energy.dds");
	buf_obj_e->n = __BUFFER_GEN_N;

	gl_define_buf_obj(buf_obj_e, &buf_obj_attr, buf_obj_e->n);

	gl_define_texture(&buf_obj_e->ID, &buf_obj_e->texture, 0);

	g_ENERGY.graphics_buf = buf_obj_e;
}

void info_indicator(const VEC2* cam_pos, int hearts, int energy) {
	int i = 0;

	g_HEART.position = *cam_pos;
	g_HEART.position.x += __HEART_WHERE.x;
	g_HEART.position.y += __HEART_WHERE.y;

	g_ENERGY.position = g_HEART.position;
	
	for (i = 0; i < hearts; i++) {
		g_HEART.position.x += __HEART_INTERVAL;
		fixed_draw_ent(&g_HEART, hearts);
	}

	g_ENERGY.position.y -= __DIST_BETWEEN_H_E;

	for (i = 0; i < hearts; i++) {
		g_ENERGY.position.x += __HEART_INTERVAL;
		fixed_draw_ent(&g_ENERGY, hearts);
	}
}
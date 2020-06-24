#include "text.h"

void Text_drew(char* text, int pos_x, int pos_y, double font_size, double letter_spacing) {

	VEC2 text_pos = (VEC2){ 1 / 16.0f, 0 / 16.0f };

	VEC2 pos = (VEC2){ pos_x, pos_y };

	int base = 0;

	int x = 0;
	int y = 0;

	int i = 0;

	g_TEXT.position = pos;
	g_TEXT.buf_z = 0;

	for (i = 0; i < strlen(text); i++) {
		base = text[i] - 32;

		x = base % 16;
		y = base / 16;

		g_TEXT.texture_pos = (VEC2){ (double)x / 16.0f, (double)y / 16.0f };

		g_TEXT.position.x += font_size - letter_spacing;
		g_TEXT.buf_z += 0.0001f;

		draw_ent(&g_TEXT);
	}
}

void text_load() {
	init_ent(&g_TEXT);
	GLuint texture = 0;
	BUFFER_OBJECT* buf_obj = NULL;
	GLfloat buf_vertice[32] = { 0 };

	BUFFER_ATTRIBUTES buf_obj_attr = {
	   buf_vertice,
	   sizeof(buf_vertice),
	   g_SQUARE_INDICES,
	   sizeof(g_SQUARE_INDICES)
	};

	set_square_vertices(buf_vertice, (VEC2) {__FONT_SIZE, __FONT_SIZE}, 3.0f, (VEC2) { 1 / 16.0f, 1 / 16.0f });

	texture = gl_load_DDS("../../resource/texture/font/test.dds");

	buf_obj = (BUFFER_OBJECT*)malloc(sizeof(BUFFER_OBJECT));
	buf_obj_init(buf_obj);

	buf_obj->ID = g_shader_id;
	buf_obj->texture = texture;
	buf_obj->n = __BUFFER_GEN_N;

	gl_define_buf_obj(buf_obj, &buf_obj_attr, buf_obj->n);

	gl_define_texture(&buf_obj->ID, &buf_obj->texture, 0);

	g_TEXT.graphics_buf = buf_obj;
}
#include <memory.h>
#include "sound.h"

#include "opengl/system.h"
#include "opengl/buffer_obj.h"

#include "vector2.h"
#include "memory.h"

#include "stage/screen_common.h"

int main() {
	
	int result = 0;

	OBJECT* obj_converter = 0;
	FORCE f_inserter = generate_force((VEC2) { 0, 0 }, __F_FOR_CONTROL__);
	ENTITY ent_inserter;

	FORCE test_f_inserter = generate_force((VEC2) { 0, 0 }, __F_ACCELERATE__);
	test_f_inserter.accel_vec = (VEC2){ 0, 1 };

	GLfloat buf_vertice[32] = { 0 };

	BUFFER_ATTRIBUTES buf_obj_attr = {
		buf_vertice,
		sizeof(buf_vertice),
		g_SQUARE_INDICES,
		sizeof(g_SQUARE_INDICES)
	};

	init_ent(&ent_inserter);			   // ��ƼƼ ����

	memcpy(buf_vertice, g_SQUARE_VERTICES, sizeof(buf_vertice));

	// ----- Initialize	----------

	// - OpenGl

	WINDOW g_window; // ������
	result = gl_system_init(&g_window, 1280, 960, "_Escape project"); // ������ ȭ�� �ʱ�ȭ �� ����
	if (result != 0)
		return 0;

	// - System Memmory

	init_memory();						 // �޸� �ʱ�ȭ
	printf(" * init_complate \n\n");

	// - Load textures

	load_texture_package("../../resource/json/models.json", NULL);

	init_indicator();

	set_square_vertices(buf_vertice, (VEC2) { 42.0f, -28.0f }, 0.0f, (VEC2) { 1.0f, 1.0f });

	g_buf_obj_insert("background",
		gl_load_BMP("../../resource/texture/background/background_S01.bmp"),
		&buf_obj_attr);

	set_square_vertices(buf_vertice, (VEC2) { 10.0f, -10.0f }, 0.0f, (VEC2) { 1.0f, 1.0f });

	g_buf_obj_insert("inventory",
		gl_load_DDS("../../resource/texture/item/inventory.dds"),
		&buf_obj_attr);

	text_load();
	init_screen();						// ��ũ�� �ʱ�ȭ

	// - run
	PlayMusic(background_bgm);		// ���� ����

	gl_system_run(&g_window);			//

	// - OpenGl
	gl_system_shutdown(&g_window);		//

	// - System Memeory
	release_memory();					// �޸� ����

	// ---------------------------
	
	return 0;
}
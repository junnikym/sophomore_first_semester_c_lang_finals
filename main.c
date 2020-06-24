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

	init_ent(&ent_inserter);			   // 엔티티 삽입

	memcpy(buf_vertice, g_SQUARE_VERTICES, sizeof(buf_vertice));

	// ----- Initialize	----------

	// - OpenGl

	WINDOW g_window; // 윈도우
	result = gl_system_init(&g_window, 1280, 960, "_Escape project"); // 윈도우 화면 초기화 및 생성
	if (result != 0)
		return 0;

	// - System Memmory

	init_memory();						 // 메모리 초기화
	printf(" * init_complate \n\n");

	// - Load textures

	text_load();
	init_screen();						// 스크린 초기화

	// - run

	gl_system_run(&g_window);			//

	// - OpenGl
	gl_system_shutdown(&g_window);		//

	// - System Memeory
	release_memory();					// 메모리 갱신

	// ---------------------------
	
	return 0;
}
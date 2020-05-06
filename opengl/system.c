#include "system.h"

int gl_system_init(WINDOW* p_out, int width, int height, const char* title) {
	int result = 0;

	glfwSetErrorCallback(err_callback);

	// GLFW �ʱ�ȭ
	if (!glfwInit()) {
		fprintf(stderr, "fail to initialize GLFW\n");
		return -1;
	}

	// window setting
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);						// OpenGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);						//
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		// ������ api ���� - core profile�� ���� �Ǿ���
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);				// Mac OS ȭȯ�� ���� ����
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);							// ������ ũ�� ����
	glfwWindowHint(GLFW_SAMPLES, 4);									// Anti-Aliasing �ɼ��� 4�� ���� 
																		// * Anti-Aliasing : ����ġ�� �ѷ��� �𼭸��� ���ױ׷� ǥ���Ͽ� �ڿ������� ����
	p_out->window = glfwCreateWindow(
		width,		// window size	| x
		height,		//				| y
		title,		// title;
		NULL,
		NULL
	);
	if (!p_out->window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(p_out->window);

	glfwSetKeyCallback(p_out->window, key_callback);		// Ű���� �ݹ��Լ� ���
	glfwSetFramebufferSizeCallback(p_out->window, gl_frame_buf_size_callback);

	// GLEW �ʱ�ȭ
	glewExperimental = GL_TRUE;
	GLenum err_code = glewInit();
	if (GLEW_OK != err_code) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err_code));

		glfwTerminate();
		return -1;
	}

	// GLEW 3.3 ������ �ƴ� ��� �������� ����
	if (!GLEW_VERSION_3_3) {
		fprintf(stderr, "OpenGL 3.3 API is not available \n");

		glfwTerminate();
		return -1;
	}

	printf("OpenGL version : %s\n", glGetString(GL_VERSION));
	printf("GLSL version : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	printf("Vendor : %s\n", glGetString(GL_VENDOR));
	printf("Renderer : %s\n", glGetString(GL_RENDERER));

	// VSync ���� : ȭ�� ������� ���� �������� ����
	glfwSwapInterval(1);

	gl_create_shader_buf ( &g_buf_obj, "main", &g_SQUARE_DATA );
	
	gl_load_texture ( &g_buf_obj.ID, "../../resource/texture/wall.bmp", &g_buf_obj.texture ),
	gl_define_texture ( 
		&g_buf_obj.ID,
		&g_buf_obj.texture,
		0
	);

	return 0;
}

void gl_system_run(WINDOW* window_struct) {
	double last_time = glfwGetTime();
	double current_time = 0;
	int n_frames = 0;
	unsigned int transformLoc = 0;
	int result = 0;

	while (!glfwWindowShouldClose(window_struct->window)) {

		current_time = glfwGetTime();
		n_frames++;

		if (current_time - last_time >= 1.0) {
			printf("%f ms/frame  %d fps \n", (1000.0 / (double)n_frames), n_frames);

			n_frames = 0;
			last_time = current_time;
		}

		gl_clear_screen();

		gl_draw_obj ( &g_buf_obj );

		glfwPollEvents();				// �̺�Ʈ �׽� ��� <-> glfwWaitEvents() : �̺�Ʈ�� �������� ����

		glfwSwapBuffers(window_struct->window);		// ���� ���۸� ���
	}
}

void gl_system_shutdown(WINDOW* window_struct) {
	glUseProgram(0);
	glBindVertexArray(0);

	glDeleteProgram( g_buf_obj.ID );
	gl_shutdown_graphics( &g_buf_obj );
	
	glfwTerminate();
}
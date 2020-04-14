#include "system.h"

WINDOW* gl_system_init(int width, int height, const char* title) {
	WINDOW* window_struct = malloc(sizeof(WINDOW));
	int result = 0;

	glfwSetErrorCallback(err_callback);

	// GLFW �ʱ�ȭ
	if (!glfwInit()) {
		fprintf(stderr, "fail to initialize GLFW\n");
		exit(EXIT_FAILURE);
	}

	// window setting
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);						// OpenGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);						//
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		// ������ api ���� - core profile�� ���� �Ǿ���
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);				// Mac OS ȭȯ�� ���� ����
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);							// ������ ũ�� ����
	glfwWindowHint(GLFW_SAMPLES, 4);									// Anti-Aliasing �ɼ��� 4�� ���� 
																		// * Anti-Aliasing : ����ġ�� �ѷ��� �𼭸��� ���ױ׷� ǥ���Ͽ� �ڿ������� ����
	window_struct->window = glfwCreateWindow(
		width,		// window size	| x
		height,		//				| y
		title,		// title;
		NULL,
		NULL
	);
	if (!window_struct->window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window_struct->window);

	glfwSetKeyCallback(window_struct->window, key_callback);		// Ű���� �ݹ��Լ� ���
	glfwSetFramebufferSizeCallback(window_struct->window, gl_frame_buf_size_callback);

	// GLEW �ʱ�ȭ
	glewExperimental = GL_TRUE;
	GLenum err_code = glewInit();
	if (GLEW_OK != err_code) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err_code));

		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// GLEW 3.3 ������ �ƴ� ��� �������� ����
	if (!GLEW_VERSION_3_3) {
		fprintf(stderr, "OpenGL 3.3 API is not available \n");

		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	printf("OpenGL version : %s\n", glGetString(GL_VERSION));
	printf("GLSL version : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	printf("Vendor : %s\n", glGetString(GL_VENDOR));
	printf("Renderer : %s\n", glGetString(GL_RENDERER));

	result = gl_load_shaders(
		"../../opengl/shader/vertex_shader.vs",
		"../../opengl/shader/fragment_shader.fs",
		window_struct->program_id
	);
	if (result != 0) {
		fprintf(stderr, "fail to create shader program\n");

		glfwTerminate();
		exit(EXIT_FAILURE);
	}


	result = gl_define_vertex_arr_obj(window_struct->program_id);
	if (result != 0) {
		fprintf(stderr, "fail to create shader program\n");

		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// VSync ���� : ȭ�� ������� ���� �������� ����
	glfwSwapInterval(1);

	return window_struct;
}

void gl_system_run(WINDOW* window_struct) {
	double last_time = glfwGetTime();
	double current_time = 0;
	int n_frames = 0;

	glUseProgram(window_struct->program_id);
	glBindVertexArray(triangle_vertex_arr_obj);

	while (!glfwWindowShouldClose(window_struct->window)) {

		current_time = glfwGetTime();
		n_frames++;

		if (current_time - last_time >= 1.0) {
			printf("%f ms/frame  %d fps \n", (1000.0 / (double)n_frames), n_frames);

			n_frames = 0;
			last_time = current_time;
		}

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window_struct->window);		// ���� ���۸� ���
		glfwPollEvents();				// �̺�Ʈ �׽� ��� <-> glfwWaitEvents() : �̺�Ʈ�� �������� ����
	}
}

void gl_system_shutdown(WINDOW* window_struct) {
	glUseProgram(0);
	glBindVertexArray(0);

	glDeleteProgram(window_struct->program_id);
	glDeleteBuffers(1, &vertex_buf);
	glDeleteBuffers(1, &color_buf);
	glDeleteVertexArrays(1, &triangle_vertex_arr_obj);
	glfwTerminate();
}
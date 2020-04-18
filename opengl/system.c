#include "system.h"

int gl_system_init(WINDOW* p_out, int width, int height, const char* title) {
	int result = 0;

	glfwSetErrorCallback(err_callback);

	// GLFW 초기화
	if (!glfwInit()) {
		fprintf(stderr, "fail to initialize GLFW\n");
		return -1;
	}

	// window setting
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);						// OpenGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);						//
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		// 오래된 api 제외 - core profile이 지원 되야함
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);				// Mac OS 화환을 위한 설정
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);							// 윈도우 크기 고정
	glfwWindowHint(GLFW_SAMPLES, 4);									// Anti-Aliasing 옵션을 4로 지정 
																		// * Anti-Aliasing : 지나치게 뚜렷한 모서리를 뭉뚱그려 표현하여 자연스럽게 만듦
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

	glfwSetKeyCallback(p_out->window, key_callback);		// 키보드 콜백함수 등록
	glfwSetFramebufferSizeCallback(p_out->window, gl_frame_buf_size_callback);

	// GLEW 초기화
	glewExperimental = GL_TRUE;
	GLenum err_code = glewInit();
	if (GLEW_OK != err_code) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err_code));

		glfwTerminate();
		return -1;
	}

	// GLEW 3.3 버전이 아닐 경우 실행하지 않음
	if (!GLEW_VERSION_3_3) {
		fprintf(stderr, "OpenGL 3.3 API is not available \n");

		glfwTerminate();
		return -1;
	}

	printf("OpenGL version : %s\n", glGetString(GL_VERSION));
	printf("GLSL version : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	printf("Vendor : %s\n", glGetString(GL_VENDOR));
	printf("Renderer : %s\n", glGetString(GL_RENDERER));

	result = gl_load_shaders(
		"../../opengl/shader/vertex_shader.vs",
		"../../opengl/shader/fragment_shader.fs",
		&(p_out->program_id)
	);
	if (result != 0) {
		fprintf(stderr, "fail to create shader program\n");

		glfwTerminate();
		return -1;
	}

	// VSync 설정 : 화면 재생률에 따라 프레임을 고정
	glfwSwapInterval(1);

	return 0;
}

void gl_system_run(WINDOW* window_struct) {
	double last_time = glfwGetTime();
	double current_time = 0;
	int n_frames = 0;
	unsigned int transformLoc = 0;
	int result = 0;

	gl_create_vertex_buf("test", &g_SQUARE_DATA, window_struct->program_id, &vertex_buffers);
 
	glUseProgram(window_struct->program_id); // -> included gl_create_vertex_buf function


	while (!glfwWindowShouldClose(window_struct->window)) {

		current_time = glfwGetTime();
		n_frames++;

		if (current_time - last_time >= 1.0) {
			printf("%f ms/frame  %d fps \n", (1000.0 / (double)n_frames), n_frames);

			n_frames = 0;
			last_time = current_time;
		}

		gl_rander(&window_struct->program_id);

		glfwPollEvents();				// 이벤트 항시 대기 <-> glfwWaitEvents() : 이벤트가 있을때만 실행

		glfwSwapBuffers(window_struct->window);		// 더블 버퍼링 사용
	}
}

void gl_system_shutdown(WINDOW* window_struct) {
	glUseProgram(0);
	glBindVertexArray(0);

	glDeleteProgram(window_struct->program_id);
	gl_shutdown_graphics();
	
	glfwTerminate();
}
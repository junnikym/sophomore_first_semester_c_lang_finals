#include "system.h"

void err_callback(int err_code, const char* err_description) {
	fprintf(stderr, "Error : %s\n", err_description);
}

void key_callback(GLFWwindow* window, int key, int scan_code, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)			// esc키 입력 시 종료
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

WINDOW* gl_init(int width, int height, const char* title) {
	WINDOW* window = malloc(sizeof(WINDOW));

	glfwSetErrorCallback(err_callback);

	// GLFW 초기화
	if (!glfwInit()) {
		fprintf(stderr, "fail to initialize GLFW\n");
		exit(EXIT_FAILURE);
	}

	// window setting
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);						// OpenGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);						//
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		// 오래된 api 제외 - core profile이 지원 되야함
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);				// Mac OS 화환을 위한 설정
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);							// 윈도우 크기 고정
	glfwWindowHint(GLFW_SAMPLES, 4);									// Anti-Aliasing 옵션을 4로 지정 
																		// * Anti-Aliasing : 지나치게 뚜렷한 모서리를 뭉뚱그려 표현하여 자연스럽게 만듦
	window = glfwCreateWindow(
		width,		// window size	| x
		height,		//				| y
		title,	// title;
		NULL,
		NULL
	);
	if (!window)	return -1;

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);		// 키보드 콜백함수 등록

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

	// VSync 설정 : 화면 재생률에 따라 프레임을 고정
	glfwSwapInterval(1);

	// VSync 설정 : 화면 재생률에 따라 프레임을 고정
	glfwSwapInterval(1);

	return window;
}

void gl_run(WINDOW* window) {
	double last_time = glfwGetTime();
	int n_frames = 0;

	while (!glfwWindowShouldClose(window)) {

		double current_time = glfwGetTime();
		n_frames++;

		if (current_time - last_time >= 1.0) {
			printf("%f ms/frame  %d fps \n", (1000.0 / (double)n_frames), n_frames);

			n_frames = 0;
			last_time = current_time;
		}

		glClearColor(0, 0, 1, 0);

		glClear(GL_COLOR_BUFFER_BIT);


		glfwSwapBuffers(window);		// 더블 버퍼링 사용
		glfwPollEvents();				// 이벤트 항시 대기 <-> glfwWaitEvents() : 이벤트가 있을때만 실행
	}
}
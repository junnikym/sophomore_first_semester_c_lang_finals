#include "system.h"

void err_callback(int err_code, const char* err_description) {
	fprintf(stderr, "Error : %s\n", err_description);
}

void key_callback(GLFWwindow* window, int key, int scan_code, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)			// escŰ �Է� �� ����
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

WINDOW* gl_init(int width, int height, const char* title) {
	WINDOW* window = malloc(sizeof(WINDOW));

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
	window = glfwCreateWindow(
		width,		// window size	| x
		height,		//				| y
		title,	// title;
		NULL,
		NULL
	);
	if (!window)	return -1;

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);		// Ű���� �ݹ��Լ� ���

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

	// VSync ���� : ȭ�� ������� ���� �������� ����
	glfwSwapInterval(1);

	// VSync ���� : ȭ�� ������� ���� �������� ����
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


		glfwSwapBuffers(window);		// ���� ���۸� ���
		glfwPollEvents();				// �̺�Ʈ �׽� ��� <-> glfwWaitEvents() : �̺�Ʈ�� �������� ����
	}
}
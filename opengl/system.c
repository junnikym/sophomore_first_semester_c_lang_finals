#include "system.h"

int gl_system_init(WINDOW* p_out, int width, int height, const char* title) {
	// Initialise GLFW
	if ( !glfwInit() ) {
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}
		
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// Open a window and create its OpenGL context
	p_out->window = glfwCreateWindow( width, height, title, NULL, NULL);
	if( p_out->window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. \n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(p_out->window);

	// Initialize GLEW
	glewExperimental = GL_TRUE; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
	
	// Ensure we can capture the escape key being pressed below
	glfwSetKeyCallback(p_out->window, key_callback);
	glfwSetFramebufferSizeCallback(p_out->window, gl_frame_buf_size_callback);
	
	glfwSwapInterval(1);

	return 0;
}

void gl_system_run(WINDOW* window) {

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	
	do {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		
		
		// Swap buffers
		glfwSwapBuffers(window->window);
		glfwPollEvents();

	} while ( !glfwWindowShouldClose(window->window) );

}

void gl_system_shutdown(WINDOW* window) {
	glfwTerminate();
}

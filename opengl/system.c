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

	// -!-!- for test -!-!-

	g_buf_obj.ID = gl_load_shader (
		"../../opengl/shader/TransformVertexShader.vs",
		"../../opengl/shader/TextureFragmentShader.fs" 
	);

	gl_define_buf_obj ( "obj", &g_buf_obj, &g_SQUARE_DATA );

	g_buf_obj.texture = gl_load_BMP("../../resource/texture/wall.bmp");

	gl_define_texture ( &g_buf_obj.ID, &g_buf_obj.texture, 0 );

	// -!-!-!-!-!-!-!-!-!-!-

	return 0;
}

void gl_system_run(WINDOW* window) {

	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	mat4 Projection = GLM_MAT4_IDENTITY_INIT;

	// Camera matrix
	mat4 View = GLM_MAT4_IDENTITY_INIT;
	
	// Model matrix : an identity matrix (model will be at the origin)
	mat4 Model = GLM_MAT4_IDENTITY_INIT;

	// Our ModelViewProjection : multiplication of our 3 matrices
	mat4 MVP = GLM_MAT4_IDENTITY_INIT;

	glm_perspective ( 45.0f, 1024.0f / 768.0f, 0.1f, 100.0f, Projection );
	
	glm_lookat (
		(vec3) { 3, 3, 3 }, 	// Camera is at (4,3,3), in World Space
		(vec3) { 0, 0, 0 }, 	// and looks at the origin
		(vec3) { 0, 1, 0 }, 	// Head is up (set to 0,-1,0 to look upside-down)
		View
	);

	glm_mat4_mul ( Projection, View, MVP );
	glm_mat4_mul ( MVP, Model, MVP ); // Remember, matrix multiplication is the other way around


	// Dark blue background
	gl_clear_screen();
	
	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	
	do {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		gl_draw_obj ( &g_buf_obj, &g_2D_ATTR_SIZE, &MVP );
		
		gl_rander();
		
		// Swap buffers
		glfwSwapBuffers(window->window);
		glfwPollEvents();

	} while ( !glfwWindowShouldClose(window->window) );

}

void gl_system_shutdown(WINDOW* window) {
	gl_shutdown_graphics( &g_buf_obj );
	glfwTerminate();
}

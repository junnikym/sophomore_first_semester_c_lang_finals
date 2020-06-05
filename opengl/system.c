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
	//-------------------
	/*
	gl_define_buf_obj ( &g_buf_obj, &g_SQUARE_DATA, 1 );

	g_buf_obj.texture = gl_load_DDS(
		"../../resource/texture/character/player_walk_sprite.dds"
	);

	gl_define_texture ( &g_buf_obj.ID, &g_buf_obj.texture, 0 );
	
	
	
	g_test_buf_obj.ID = g_buf_obj.ID;
	
	gl_define_buf_obj ( &g_test_buf_obj, &g_TESTER_DATA, 1 );
	
	g_test_buf_obj.texture = gl_load_BMP(
		"../../resource/texture/wall.bmp"
	);
	
	gl_define_texture ( &g_test_buf_obj.ID, &g_test_buf_obj.texture, 0 );
	
	//-------------------
	
	inserter.graphics_buf = &g_buf_obj;
	set_essential_f_ent(&inserter);
	
	g_obj_alter( __ENTITY__, &inserter, g_user_obj_i, -1 );
	
	release_ent(&inserter);
	
	second_ins.graphics_buf = &g_test_buf_obj;
	second_ins.position.x = 2.5f;
	
	g_obj_alter( __ENTITY__, &second_ins, 1, -1 );
	
	//g_buf_obj_insert ( "user_charactor",)
	*/
	// -!-!-!-!-!-!-!-!-!-!-
	
	
	// --- camera setting
	
	gl_set_FOV(45.0f);
	
	gl_set_projection();
	
	gl_set_view (
		(vec3) { 0, 0, 10 } ,
		GLM_VEC3_ZERO,
		(vec3) { 0, 1, 0 }
	);

	return 0;
}

void gl_system_run(WINDOW* window) {
	// Dark blue background
	gl_clear_screen();
	
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	
	do {
		
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		update_g_obj();

		gl_rander();
		
		// Swap buffers
		glfwSwapBuffers(window->window);
		glfwPollEvents();

	} while ( !glfwWindowShouldClose(window->window) );

}

void gl_system_shutdown(WINDOW* window) {
	gl_shutdown_graphics( &g_buf_obj );
	gl_shutdown_graphics( &g_test_buf_obj );
	glfwTerminate();
}

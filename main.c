#include "opengl/system.h"
#include "types.h"
#include "memory.h"

// --- for control memory.h's data
extern DYN_ARR g_objects;
extern OBJECT g_user_obj;

int main() {
	int result = 0;
	OBJECT* obj_converter = 0;
	FORCE f_inserter = generate_force( (VEC2){ 0,  0 }, F_FOR_CONTROL | F_PAUSE );

// ----- Initialize	----------

	// ----- OpenGl
	WINDOW g_window;
	result = gl_system_init(&g_window, 800, 600, "Test window");
	if (result != 0)
		return 0;
	// ----- System Memmory
	init_memory();

	// -!-!- for test -!-!-

	dyn_arr_push_back( &g_user_obj.entities, NULL, copy_ent );
	set_center_obj( &g_user_obj, 0 );
	
	f_inserter.force_vec.x = -0.1;
	dyn_arr_push_back( &(g_user_obj.center->forces), &f_inserter, copy_force );	// [0] : left;
	
	f_inserter.force_vec.x = 0.1;
	dyn_arr_push_back( &(g_user_obj.center->forces), &f_inserter, copy_force );	// [1] : right;
	
	// -!-!--!-!--!-!--!-!-

// ---------------------------
// ----- run	--------------

	gl_system_run(&g_window);

// ---------------------------
// ----- Initialize	----------

	// ----- OpenGl
	gl_system_shutdown(&g_window);
	// ----- System Memmory
	release_memory();

// ---------------------------
	return 0;
}

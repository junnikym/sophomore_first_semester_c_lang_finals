#include "opengl/system.h"
#include "types.h"
#include "memory.h"

int main() {
	int result = 0;
	OBJECT* obj_converter = 0;
	FORCE f_inserter = generate_force( (VEC2){ 0,  0 }, F_FOR_CONTROL );

// ----- Initialize	----------

	// ----- System Memmory
	init_memory();
	printf(" * init_complate \n\n");

// ===== set elements 		=====
// =	==== OBJECT 0	================================================== //
	push_obj_into_g_obj( NULL ); // OBJ 0
		push_ent_into_g_obj( NULL, 0 );	// ENT 0-> 0
			push_force_into_g_obj( NULL, 0, 0 );	// FORCE 0-> 0-> 0
			push_force_into_g_obj( NULL, 0, 0 );	// FORCE 0-> 0-> 1
			push_force_into_g_obj( NULL, 0, 0 );	// FORCE 0-> 0-> 2
		push_ent_into_g_obj( NULL, 0 );	// ENT 0-> 1
			push_force_into_g_obj( NULL, 0, 1 );	// FORCE 0-> 1-> 0
			push_force_into_g_obj( NULL, 0, 1 );	// FORCE 0-> 1-> 1
		push_ent_into_g_obj( NULL, 0 );	// ENT 0-> 2
			push_force_into_g_obj( NULL, 0, 2 );	// FORCE 0-> 2-> 0
		push_ent_into_g_obj( NULL, 0 );	// ENT 0-> 3
		
// =	==== OBJECT 1	================================================== //
	push_obj_into_g_obj( NULL );	// OBJ 1
		push_ent_into_g_obj( NULL, 1 );	// ENT 1-> 0
			push_force_into_g_obj( NULL, 1, 0 );	// FORCE 1-> 0-> 0
			push_force_into_g_obj( NULL, 1, 0 );	// FORCE 1-> 0-> 1
		push_ent_into_g_obj( NULL, 1 );	// ENT 1-> 1
			push_force_into_g_obj( NULL, 1, 1 );	// FORCE 1-> 1-> 0
		push_ent_into_g_obj( NULL, 1 );	// ENT 1-> 2
		
// =	==== OBJECT 2	================================================== //
	push_obj_into_g_obj( NULL );	// OBJ 2
		push_ent_into_g_obj( NULL, 2 );	// ENT 2-> 0
			push_force_into_g_obj( NULL, 2, 0 );	// FORCE 2-> 0-> 0
		push_ent_into_g_obj( NULL, 2 );	// ENT 2-> 1
		
// =	==== OBJECT 3	================================================== //
	push_obj_into_g_obj( NULL );	// OBJ 3
		push_ent_into_g_obj( NULL, 3 );	// ENT 3-> 0
	
// =	================================================================== //

	// -!-!- for test -!-!-

	//dyn_arr_push_back( &g_user_obj.entities, NULL, copy_ent );
	//set_center_obj( &g_user_obj, 0 );
	
	//dyn_arr_push_back( &(g_user_obj.center->forces), &f_inserter, copy_force );
	
	// -!-!--!-!--!-!--!-!-
	
	// ----- OpenGl
	WINDOW g_window;
	result = gl_system_init(&g_window, 800, 600, "Test window");
	if (result != 0)
		return 0;

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

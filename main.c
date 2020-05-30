#include "opengl/system.h"
#include "vector2.h"
#include "memory.h"

int main() {
	int result = 0;
	OBJECT* obj_converter = 0;
	FORCE f_inserter = generate_force( (VEC2){ 0,  0 }, __F_FOR_CONTROL__ );

// ----- Initialize	----------

	// ----- OpenGl
	WINDOW g_window;
	result = gl_system_init ( &g_window, 800, 600, "Test window" );
	if ( result != 0 )
		return 0;

	// ----- System Memmory
	init_memory();
	printf(" * init_complate \n\n");

// ===== set elements 		=====
// =	==== OBJECT 0	================================================== //
	g_obj_push_thing ( __OBJECT__, NULL ); // OBJ 0
		g_obj_push_thing ( __ENTITY__, NULL, 0 );	// ENT 0-> 0
			g_obj_push_thing ( __FORCE__, NULL, 0, 0 );	// FORCE 0-> 0-> 0

	g_obj_set_center_ent ( 0, 0 );
	g_obj_set_user_obj(0);
		
// =	==== OBJECT 1	================================================== //
	g_obj_push_thing ( __OBJECT__, NULL );	// OBJ 1
		g_obj_push_thing ( __ENTITY__, NULL, 1 );	// ENT 1-> 0
			g_obj_push_thing ( __FORCE__, NULL, 1, 0 );	// FORCE 1-> 0-> 0

	g_obj_set_center_ent ( 1, 0 );
		
// =	==== OBJECT 2	================================================== //
	g_obj_push_thing ( __OBJECT__, NULL );	// OBJ 2
		g_obj_push_thing ( __ENTITY__, NULL, 2 );	// ENT 2-> 0
			g_obj_push_thing ( __FORCE__, NULL, 2, 0 );	// FORCE 2-> 0-> 0

	g_obj_set_center_ent ( 2, 0 );
		
// =	==== OBJECT 3	================================================== //
	g_obj_push_thing ( __OBJECT__, NULL );	// OBJ 3
		g_obj_push_thing ( __ENTITY__, NULL, 2 );	// ENT 3-> 0
			g_obj_push_thing ( __FORCE__, NULL, 2, 0 );	// FORCE 3-> 0-> 0

	g_obj_set_center_ent ( 3, 0 );
	
// =	================================================================== //

	// -!-!- for test -!-!-

	//dyn_arr_push_back( &g_user_obj.entities, NULL, copy_ent );
	//set_center_obj( &g_user_obj, 0 );
	
	//dyn_arr_push_back( &(g_user_obj.center->forces), &f_inserter, copy_force );
	
	// -!-!--!-!--!-!--!-!-

// ---------------------------
// ----- run	--------------

	gl_system_run(&g_window);

// ---------------------------
// ----- Initialize	----------

	// ----- OpenGl
	gl_system_shutdown(&g_window);
	// ----- System Memeory
	release_memory();

// ---------------------------
	return 0;
}

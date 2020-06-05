#include "opengl/system.h"
#include "opengl/buffer_obj.h"

#include "vector2.h"
#include "memory.h"

int main() {
	int result = 0;
	OBJECT* obj_converter = 0;
	FORCE f_inserter = generate_force( (VEC2){ 0,  0 }, __F_FOR_CONTROL__ );
	ENTITY ent_inserter;
	
	/*	position index		|	texture coords index
	 *	 0	 1	 2			|	6	 7
	 *	 8	 9	10			|	14	15
	 *	16	17	18			|	22	23
	 *	24	25	26			|	30	31
	 */
	
	BUFFER_ATTRIBUTES buf_obj_attr = {
		&g_SQUARE_VERTICES,
		sizeof(g_SQUARE_VERTICES),
		&g_SQUARE_INDICES,
		sizeof(g_SQUARE_INDICES)
	};
	
	init_ent ( &ent_inserter );

// ----- Initialize	----------

// - System Memmory
	init_memory();
	printf(" * init_complate \n\n");
	
// - OpenGl
	WINDOW g_window;
	result = gl_system_init ( &g_window, 800, 600, "Test window" );
	if ( result != 0 )
		return 0;
	
// - Load textures

/*----- USER CHARACTOR	--------------------------------------------------*/
	
	g_buf_obj_insert ( "charactor",
					   gl_load_DDS("../../resource/texture/character/player_walk_sprite.dds"),
					   &g_SQUARE_DATA );
	
/*----- WALL 1			--------------------------------------------------*/
	g_buf_obj_insert ( "wall",
					   gl_load_DDS("../../resource/texture/wall.bmp"),
					   &g_SQUARE_DATA );
	
// - Set g_object
	
/*----- OBJECT 0 	------------------------------------------------------------*/
/* | */	g_obj_push_thing ( __OBJECT__, NULL );
/* |		-- [0] : ENTITY 0		*/
/* | */	g_obj_push_thing ( __ENTITY__, NULL, 0 );
/* | */	g_obj_set_center_ent ( 0, 0 );
/* | */	g_obj_set_essential_f( 0, -1 );
/* | */	g_obj_set_obj_buf("charactor", 0, -1);	// set texture
/* | */
/* | */	g_obj_set_user_obj(0);
/*------------------------------------------------------------------------------*/
/*----- OBJECT 1 	------------------------------------------------------------*/
/* | */	g_obj_push_thing ( __OBJECT__, NULL );
/* |		-- [1] : ENTITY 0		*/
/* | */	g_obj_push_thing ( __ENTITY__, NULL, 1 );
/* | */	g_obj_set_center_ent ( 1, 0 );
/* | */	g_obj_set_essential_f( 1, -1 );
/* | */	g_obj_set_obj_buf("wall", 1, -1);		// set texture
/* | */
/* | */	g_obj_set_user_obj(0);
/*------------------------------------------------------------------------------*/

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

#include <memory.h>

#include "opengl/system.h"
#include "opengl/buffer_obj.h"

#include "vector2.h"
#include "memory.h"
#include "load_json.h"

int main() {
	int result = 0;
	
	int screen_w = 1200;
	int screen_h = 800;
	
	OBJECT* obj_converter = 0;
	ENTITY ent_inserter;

	FORCE f_inserter = { 0 };
	
	GLfloat buf_vertice[32] = { 0 };
	
	BUFFER_ATTRIBUTES buf_obj_attr = {
		buf_vertice,
		sizeof(buf_vertice),
		g_SQUARE_INDICES,
		sizeof(g_SQUARE_INDICES)
	};
	
	 memcpy(buf_vertice, g_SQUARE_VERTICES, sizeof(buf_vertice));

// ----- Initialize	----------
	
// - OpenGl
	
	WINDOW g_window;
	result = gl_system_init ( &g_window, screen_w, screen_h, "Test window" );
	if ( result != 0 )
		return 0;

// - System Memmory
	
	init_memory();
	printf(" * init_complate \n\n");
	
// - Load textures
	
	//load_texture_package("../../resource/json/models.json", NULL);
	
	/*----- USER CHARACTOR	--------------------------------------------------*/
	
	set_square_vertices( buf_vertice, (VEC2){2.5f, 2.5f}, 1.0f, (VEC2){1.0f/16.0f, 1.0f} );
	
	g_buf_obj_insert ( "charactor",
					    gl_load_DDS( "../../resource/texture/character/player_walk_sprite.dds" ),
					   &buf_obj_attr );

	set_square_vertices ( buf_vertice, (VEC2) { 5.0f, 5.0f }, 0.0f, (VEC2) { 2.0f / 16.0f, 1.0f } );

	g_buf_obj_insert ( "wall",
					   gl_load_BMP ( "../../resource/texture/item/item_co.bmp" ),
					   &buf_obj_attr );
	
	/*----- WALL 1			--------------------------------------------------*/
	
// - Set g_object
	
	init_force ( &f_inserter );
	f_inserter.force_vec = (VEC2){1, 1};
	f_inserter.identify = __F_ROTATE__ | __F_NON_FRICTION__;
	
/*----- OBJECT 0 	------------------------------------------------------------*/
/* |*/	g_obj_push_thing ( __OBJECT__, NULL );
/* |*/	//g_obj_set_collision_box ( 0, (VEC2){2.5f, 2.5f} );
/* |*/	g_obj_set_user_obj(0);
/* |*/
/* |		-- [0] : ENTITY 0		*/
/* |*/	g_obj_push_thing ( __ENTITY__, NULL, 0 );
/* |*/	g_obj_set_center_ent ( 0, 0 );
/* |*/	g_obj_set_essential_f( 0, -1 );
/* |*/	g_obj_set_obj_buf("charactor", 0, -1);	// set texture
/* |*/	g_obj_append_collision_box(0, (BOX){(VEC2){0.0f, 0.0f}, (VEC2){2.5f, 2.5f}});
/*------------------------------------------------------------------------------*/
/*----- OBJECT 1 	------------------------------------------------------------*/
/* |*/	g_obj_push_thing ( __OBJECT__, NULL );
/* |*/	//g_obj_set_collision_box ( 1, (VEC2){5.0f, 5.0f} );
/* |*/
/* |		-- [1] : ENTITY 0		*/
/* |*/	g_obj_push_thing ( __ENTITY__, NULL, 1 );
/* |*/	g_obj_set_center_ent ( 1, 0 );
/* |*/	g_obj_set_essential_f( 1, -1 );
/* |*/	g_obj_set_obj_buf("wall", 1, -1);		// set texture
/* |*/	g_obj_append_collision_box(1, (BOX){(VEC2){0.0f, 0.0f}, (VEC2){5.0f, 5.0f}});
/*------------------------------------------------------------------------------*/
/* |*/	g_world_insert_obj(0);
/* |*/	g_world_insert_obj(1);

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

#include "random_generator.h"

VEC2 random_place ( VEC2 center, double range ) {
	srand((int)(glfwGetTime()*1000));

	center.x -= range;
	center.y -= range;

	center.x += rand ( ) / (double)RAND_MAX * (range * 2);
	center.y += rand ( ) / (double)RAND_MAX * (range * 2);

	return center;
}

void generate_asteroid ( VEC2 where ) {
	g_obj_push_thing ( __OBJECT__, NULL );

	// -- Entity 0 -- //
	g_obj_push_thing ( __ENTITY__, NULL, 0 );
	g_obj_set_center_ent ( -1, 0 );
	g_obj_set_obj_buf ( "asteroid", 0, -1 );	// set texture
	g_obj_append_collision_box ( 0, (BOX) { (VEC2) { 1.0f, 1.0f }, (VEC2) { 8.0f, 10.0f } } );

	g_world_insert_obj ( -1 );
}

void generate_rand_asteroid ( VEC2 center, double range ) {
	int how_much = 0;
	int i = 0;

	srand ( (int)(glfwGetTime ( ) * 1000) );

	how_much = rand() % __MAX_GENERATEING;
	
	for ( i = 0; i < how_much; i++ ) {
		generate_asteroid ( random_place ( center, range ) );
	}
}
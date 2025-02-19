#include "memory.h"

// ------------------------------------------------------- //
// ----- g_textures functions	--------------------------

void* g_buf_obj_init() {
	g_buf_objs = NULL;
	g_buf_objs_size = 0;
}

void* g_buf_obj_insert ( const char* title,
						 GLuint texture,
						 BUFFER_ATTRIBUTES* attr ) {
	g_buf_objs_size++;
	
	TREE* inserter = NULL;
	BUFFER_OBJECT* buf_obj = NULL;
	
	buf_obj = (BUFFER_OBJECT*) malloc (sizeof(BUFFER_OBJECT));
	buf_obj_init(buf_obj);
	
	buf_obj->ID = g_shader_id;
	buf_obj->texture = texture;
	buf_obj->n = __BUFFER_GEN_N;
	
	gl_define_buf_obj ( buf_obj, attr, buf_obj->n );
	
	gl_define_texture ( &buf_obj->ID, &buf_obj->texture, 0 );
	
	if ( (inserter = tree_create( title, buf_obj )) == NULL )
		return NULL;
	
	g_buf_objs = tree_insert( g_buf_objs, inserter );
	
	return inserter;
}

void g_buf_obj_release_each ( TREE* each, void* free_value ) {
	BUFFER_OBJECT* target = each->value;
	
	gl_release_buf_obj( target );
	
	tree_free ( each, free_value );
}

void g_buf_obj_release () {
	int free_elem_too = 1;
	
	tree_foreach_post ( g_buf_objs, &free_elem_too, g_buf_obj_release_each );
}

// ------------------------------------------------------- //
// ----- g_object function	------------------------------

// -- push_back elements into g_object

void* g_obj_push_thing ( _OBJ_ELEM_ type, void* item, ... ) {
	va_list ap;
	va_start(ap, item);

	int i = 0;
	void* target = NULL;

	switch ( type ) {
		// --------------------------------------------------
		case __FORCE__:
			// -- Get chosen OBJECT
			i = va_arg ( ap, int );
			
			if ( i < 0 && i > g_objects.size ) {	// is in range
				printf("ERROR in g_obj_push_thing func -> out of range \n");
				printf("\t push : FORCE / error : g_objects index \n");
				return NULL;		// ERROR
			}
			
			target = dyn_arr_get(&g_objects, i);
			
			// -- Get chosen ENTITY
			i = va_arg ( ap, int );

			if( i == __CENTER_I ) {
				target = ((OBJECT*)target)->center;
			}
			else {
				if ( i < 0 && i > ((OBJECT*)target)->entities.size ) {	// is in range
					printf("ERROR in g_obj_push_thing func -> out of range \n");
					printf("\t push : FORCE / error : ENTITY index \n");
					return NULL;	// ERROR
				}
			
				target = dyn_arr_get( &((OBJECT*)target)->entities, i );
			}
			
			// -- push and return result
			target = &((ENTITY*)target)->forces;
			return dyn_arr_push_back ( target, item, copy_ent );
		// --------------------------------------------------
		case __ENTITY__:
			i = va_arg(ap, int);
			
			// -- is in range
			if ( i < 0 && i > g_objects.size )
				return NULL;

			// -- push and result
			target = &((OBJECT*)g_objects.items)[i].entities;
			return dyn_arr_push_back ( target, item, copy_ent );
		// --------------------------------------------------
		case __OBJECT__:
			return dyn_arr_push_back ( &g_objects, item, copy_obj );
		// --------------------------------------------------
	}

	return NULL;
}

// -- Setter

OBJECT* g_obj_set_user_obj ( int i ) {
	if ( i == -1 )				// 제일 끝의 요소를 사용
		i = g_objects.size;

	g_user_obj_i = i;
	g_user_obj = dyn_arr_get ( &g_objects, i );

	return g_user_obj;
}

ENTITY* g_obj_set_center_ent ( int obj_i, int ent_i ) {
	if(obj_i == -1) {
		obj_i = g_objects.size;
	}

	return set_center_obj ( dyn_arr_get ( &g_objects, obj_i ), ent_i );
}

void g_obj_set_essential_f ( int obj_i, int ent_i ) {
	void* target = dyn_arr_get (&g_objects, obj_i);
	
	if(ent_i == __CENTER_I)
		target = ((OBJECT*)target)->center;
	else
		target = dyn_arr_get( &(((OBJECT*)target)->entities), ent_i );
	
	set_essential_f_ent(target);
}

void* g_obj_set_obj_buf ( char* obj_buf_key, int obj_i, int ent_i) {
	void* result = NULL;
	void* target = dyn_arr_get( &g_objects, obj_i );
	
	ENTITY* for_debug_ent = NULL;
	BUFFER_OBJECT* for_debug = NULL;
	
	if( ent_i == -1 )
		target = ((OBJECT*)target)->center;
	
	else
		target = dyn_arr_get( &((OBJECT*)target)->entities, ent_i );
	
	result = tree_search( g_buf_objs, obj_buf_key )->value;
	if(result == NULL)
		return NULL;

	((ENTITY*)target)->graphics_buf = result;
	for_debug_ent = ((ENTITY*)target);
	for_debug = result;
	
	return target;
}

void g_obj_append_collision_box ( int obj_index, BOX box ) {
	OBJECT* target = dyn_arr_get(&g_objects, obj_index);
	
	dyn_arr_push_back(
		&(target->collision_box),
		&box,
		copy_box
	);
}

void g_obj_append_interaction_box(int obj_index, BOX box) {
	OBJECT* target = dyn_arr_get(&g_objects, obj_index);

	dyn_arr_push_back(
		&(target->interaction),
		&box,
		copy_box
	);
}

// -- check function

int is_g_user_obj_setted () {
	if(g_user_obj == NULL)
		return 0;
	
	return 1;
}

// -- Update functions

void update_each_g_obj ( void* elem, int i, void* arg ) {
	update_obj ( elem );
}

void update_g_obj ( ) {
	g_obj_foreach( NULL, update_each_g_obj );
}

void* g_obj_alter ( _OBJ_ELEM_ type, void* _rhs,
					void (*alt_func)(void* lhs, const void* rhs), ... ) {
	va_list ap;
	
	int i = 0;
	void* target = NULL;
	
	va_start(ap, alt_func);
	
	// -- Get OBJECT
	i = va_arg ( ap, int );		// OBJECT[i]
	
	if( i == __CENTER_I ) 		// USER_OBJECT
		target = g_user_obj;
	else {
		target = dyn_arr_get( &g_objects, i );
	}
	
	switch ( type ) {
		case __FORCE__:
			// -- Get ENTITY
			i = va_arg ( ap, int );		// OBJECT[i] -> ENTITY[i]
			
			if( i == __CENTER_I )
				target = ((OBJECT*)target)->center;
			else
				target = dyn_arr_get( &(((OBJECT*)target)->entities), i );
			
			// -- Get FORCE
			i = va_arg ( ap, int );		// OBJECT[i] -> ENTITY[i] -> FORCE[i]
			target = dyn_arr_get( &(((ENTITY*)target)->forces), i );
			
			// -- Alter
			alt_func ( target, _rhs );
			
			return target;
		case __ENTITY__:
			i = va_arg ( ap, int );		// OBJECT[i] -> ENTITY[i]
			
			if( i == __CENTER_I )
				target = ((OBJECT*)target)->center;
			else
				target = dyn_arr_get( &(((OBJECT*)target)->entities), i );
			
			alt_func ( target, _rhs );
			
			return target;
		case __OBJECT__:
			alt_func ( target, _rhs );
			
			return target;
	}
	
	return NULL;
}

VEC2 g_obj_get_position ( int index ) {
	if ( index == __CENTER_I ) {
		return g_user_obj->center->position;
	}
	return ((OBJECT*) dyn_arr_get (&g_objects, index))->center->position;
}

double g_obj_get_angle (int index) {
	if(index == __CENTER_I) {
		return g_user_obj->center->angle;
	}
	
	return ((OBJECT*)g_objects.items)[index].center->angle;
}

void g_obj_foreach ( void* msger, void (*func)(void* elem, int i, void* arg) ) {
	dyn_arr_foreach(&g_objects, msger, func);
}

void g_obj_init	() {
	g_user_obj = NULL;
	g_user_obj_i = -1;
	
	dyn_arr_init( &g_objects, sizeof(OBJECT) );
}

void g_obj_release() {
	int i = 0;
	OBJECT* obj_converter = NULL;
	
	obj_converter = (OBJECT*)g_objects.items;

	for ( i = 0; i <= g_objects.size; i++ ) {
		release_obj( &obj_converter[i]);
	}
	obj_converter = NULL;

	dyn_arr_release( &g_objects );
	
	g_user_obj = NULL;
	g_user_obj_i = -1;
}


// ------------------------------------------------------- //
// ----- g_world function		------------------------------

void g_world_process ( int sect_x, int sect_y, int* interaction) {
	LIST** quads = NULL;
	int quad_i = quadrant_get_index( (VEC2){sect_x, sect_y} );
	
	LIST* current = NULL;
	LIST* loop_node = NULL;
	
	OBJECT* current_obj = NULL;
	OBJECT* loop_obj = NULL;
	
	int indicator = 0;
	int interaction_indic = 0;
	WORLD_NODE* non_user = 0;

	int x_i = -1, y_i = 0;
	int interaction_stack = 0;

	// 처음으로 비교 시 무조건 비교대상으로 들어가야 하기 때문에 가장 큰 수를 넣어줌
	double interaction_comp = (double)__WORLD_UNIT;
	VEC2 dist = V2_ZERO;
	double dist_size = 0.0;
	
	quads = (g_world.world)[abs(sect_x)][abs(sect_y)].part;
	
	if(quads[quad_i] == NULL || quads[quad_i]->next == NULL)
		return;				// 비교 대상까지 2개 이상의 리스트가 존재해야함.
	
	for ( current = quads[quad_i]; current->next != NULL; current = current->next ) {
		current_obj = ((WORLD_NODE*)(current->elem))->elem;
		x_i++;
		y_i = x_i;
		
		for ( loop_node = current->next; loop_node != NULL; loop_node = loop_node->next ) {
			non_user = NULL;

			loop_obj = ((WORLD_NODE*)(loop_node->elem))->elem;
			y_i++;

			if (x_i == g_user_obj_i) {
				non_user = ((WORLD_NODE*)(loop_node->elem));
			}
			if (y_i == g_user_obj_i) {
				non_user = ((WORLD_NODE*)(current->elem));
			}

			if(non_user != NULL) {
				interaction_indic = obj_is_interaction_range(current_obj, loop_obj );

				if (!(interaction_indic & __NO_COLLIDE)) {

					dist = vec2_get_distance(
								&current_obj->center->position, 
								&loop_obj->center->position
							);

					dist_size = vec2_get_size(&dist);

					if ( interaction_comp > dist_size ) {
						interaction_comp = dist_size;
						*interaction = non_user->index;
					}

				}
			}

			indicator = obj_is_collision (current_obj, loop_obj);
			
			if( indicator == -1 )
				continue;
			
			if( indicator & __NO_COLLIDE )
				continue;
			
			else {
			//	printf(" %.2f object %p, and %p crashed ! \n", glfwGetTime(), current, loop_node);
			//	printf("\t indicator : %d (no collide : %d)\n\n", indicator& __NO_COLLIDE& __NO_COLLIDE, __NO_COLLIDE);
				
				
			}
		}
		
	}
}

void g_world_init( int _x_size, int _y_size) {
	world_init(&g_world, _x_size, _y_size);
}

void g_world_release() {
	world_release(&g_world);
}

void g_world_insert_obj ( int g_obj_index ) {
	OBJECT* obj_ptr = NULL;

	if(g_obj_index == -1)
		obj_ptr = dyn_arr_get ( &g_objects, g_objects.size );
	else
		obj_ptr = dyn_arr_get ( &g_objects, g_obj_index );

	world_insert ( &g_world, obj_ptr->center->position, obj_ptr, g_obj_index );
}

void g_world_update_obj ( void* obj, VEC2* return_pos ) {
	update_obj ( obj );

	*return_pos = ((OBJECT*)obj)->center->position;
}

void g_world_update ( int section_x, int section_y ) {
	world_update( &g_world, section_x, section_y, g_world_update_obj);
}

// ------------------------------------------------------- //
// ----- entire memory functions	----------------------

void init_memory ( ) {
	g_shader_id = gl_load_shader (
		"../../opengl/shader/TransformVertexShader.vs",
		"../../opengl/shader/TextureFragmentShader.fs"
	);

	g_buf_obj_init;
	
	g_obj_init ();
	
	g_world_init ( __WORLD_EARLY_SIZE, __WORLD_EARLY_SIZE );
}

void release_memory() {
	g_obj_release ();
	g_buf_obj_release ();
	g_world_release ();
}

// ------------------------------------------------------- //

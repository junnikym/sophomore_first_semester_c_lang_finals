#ifndef MEMORY_H
#define MEMORY_H

#include <stdarg.h>

#include "object.h"
#include "types.h"

#include "tree.h"
#include "hash_table.h"

#include "opengl/buffer_obj.h"
#include "opengl/texture.h"

#define __CENTER_I -1

#define __BUFFER_GEN_N 1

static GLuint g_shader_id;

static TREE* g_buf_objs;	// item type : BUFFER_OBJECT
static int g_buf_objs_size;

static DYN_ARR g_objects;	// item type : OBJECT
static OBJECT* g_user_obj;
static int g_user_obj_i;

//static LIST* g_map[__G_HASH_TABLE_SIZE];

// ------------------------------------------------------- //
// ----- g_textures functions	--------------------------

void* 	g_buf_obj_insert 		( const char* title,
								  GLuint texture,
								  BUFFER_ATTRIBUTES* attr);

void* 	g_buf_obj_load_comp		( FILE* file ); 	// compilation file load

static void g_buf_obj_release_each ( TREE* each, void* free_value ) ;
void	g_buf_obj_release		();

// ------------------------------------------------------- //
// ----- g_object functions	------------------------------

// -- push_back elements into g_object

void*	g_obj_push_thing		( _OBJ_ELEM_ type, void* item, ... );	// ... => index of thing

// -- Setter

OBJECT*	g_obj_set_user_obj		( int i );
ENTITY* g_obj_set_center_ent	( int obj_i, int ent_i );
void  	g_obj_set_essential_f 	( int obj_i, int ent_i );
void 	g_obj_set_collision_box ( int obj_i, VEC2 box );

void* 	g_obj_set_obj_buf		( char* obj_buf_key, int obj_i, int ent_i);

// -- check functions();

int 	is_g_user_obj_setted	();

int 	g_obj_is_collision		( int lhs_i, int rhs_i );

// -- Update functions

void	update_each_g_obj		( void* elem, int i, void* pos );
void	update_g_obj			( );

void*	g_obj_alter				( _OBJ_ELEM_ type, void* _rhs,
								 void (*alt_func)(void* lhs, const void* rhs), ... );

void*	g_obj_get_thing			( _OBJ_ELEM_ type, ... );				// ... => index of thing

void 	g_obj_foreach			( void* msger, void (*func)(void* elem, int i, void* arg) );
VEC2	g_obj_get_position		( int index );

void 	g_obj_init				( );
void 	g_obj_release 			( );

// ------------------------------------------------------- //
// ----- g_map functions	------------------------------
/*
void 	g_map_init				( );

void 	g_map_insert_hash 		( char* key, void* item );
*/
// ------------------------------------------------------- //
// ----- entire memory functions	----------------------

void init_memory ( );
void release_memory();

// ------------------------------------------------------- //

#endif

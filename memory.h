#ifndef MEMORY_H
#define MEMORY_H

#include <stdarg.h>

#include "object.h"
#include "types.h"

#include "tree.h"
#include "hash_table.h"
#include "world.h"

#include "opengl/buffer_obj.h"
#include "opengl/texture.h"

#define __CENTER_I -1

#define __BUFFER_GEN_N 1

/*
 * 		memory.h 에서는 게임에 필요한 메모리를 한대 모아 정의해 놓은 곳이다.
 *
 *		물체 등을 하나씩 생성하다보면 존재를 잊어버리고 해제를 못하는 경우가 발생
 *		할 수 있기 때문에 이를 방지하기위해 이와 같이 메모리를 모두 모아 정의하였다.
 *
 *		memory.h 에 정의된 모든 메모리들은 정적(static)으로 정의 되었기 때문에
 *		memory.h 외의 다른 파일에서 접근한다면 잘못된 주소로 접근이 되거나 오류가
 *		뜰것이다. 따라서 다음과 같이 요소들을 활용 할 수 있는 wapper함수를 정의
 *		하였으며 헤더 밖에서는 다음 함수를 사용하여 수정이 가능하다.
 */

static GLuint g_shader_id;

static TREE* g_buf_objs;	// item type : BUFFER_OBJECT
static int g_buf_objs_size;

static DYN_ARR g_objects;	// item type : OBJECT
static OBJECT* g_user_obj;
static int g_user_obj_i;

static WORLD g_world;

// ------------------------------------------------------- //
// ----- g_textures functions	--------------------------

void*   g_buf_obj_insert        ( const char* title,
								  GLuint texture,
								  BUFFER_ATTRIBUTES* attr);

static void g_buf_obj_release_each ( TREE* each, void* free_value ) ;
void	g_buf_obj_release		();

// ------------------------------------------------------- //
// ----- g_object functions	------------------------------

// -- push_back elements into g_object

void*	g_obj_push_thing		( _OBJ_ELEM_ type, void* item, ... );	// ... => index of thing

// -- Setter

OBJECT* g_obj_set_user_obj		( int i );
ENTITY* g_obj_set_center_ent	( int obj_i, int ent_i );
void  	g_obj_set_essential_f 	( int obj_i, int ent_i );
void 	g_obj_set_collision_box ( int obj_i, VEC2 box );

void* 	g_obj_set_obj_buf		( char* obj_buf_key, int obj_i, int ent_i);

void 	g_obj_append_collision_box ( int obj_index, BOX box );

// -- check functions();

int 	is_g_user_obj_setted	();
int 	g_obj_is_collision		( int lhs_i, int rhs_i );
void 	g_obj_coliision_proccess ( void* elem, int i, void* arg );

// -- Update functions

void	update_each_g_obj		( void* elem, int i, void* pos );
void	update_g_obj				( );

void*	g_obj_alter				( _OBJ_ELEM_ type, void* _rhs,
								 	  void (*alt_func)(void* lhs, const void* rhs), ... );
// -- Getter

VEC2	g_obj_get_position		( int index );
double  g_obj_get_angle			( int index );

void 	g_obj_foreach			( void* msger, void (*func)(void* elem, int i, void* arg) );

void 	g_obj_init				( );
void 	g_obj_release 			( );

// ------------------------------------------------------- //
// ----- g_world functions	------------------------------

void 	world_collsion_process ( int sect_x, int sect_y );

void 	g_world_init		( int _x_size, int _y_size );
void 	g_world_release	    ( );

void	g_world_insert_obj  ( int g_obj_index );

void 	g_world_update_obj  ( void* obj, VEC2* return_pos );
void 	g_world_update	    ( int section_x, int section_y );

// ------------------------------------------------------- //
// ----- entire memory functions	----------------------

void 	init_memory 		( );
void 	release_memory	( );

// ------------------------------------------------------- //


#endif

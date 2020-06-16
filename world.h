#ifndef WORLD_H
#define WORLD_H

#include "hash_table.h"

#include "vector2.h"

#define __WORLD_UNIT 10000
#define __WORLD_EARLY_SIZE 100
#define __WORLD_SIZE __WORLD_UNIT*__WORLD_HOW_MUCH_UNIT

typedef struct _WORLD_NODE_ {
	void* elem;					// 물체를 저장하고있는 메모리의 위치
	int index;						// g_object 등 해당 배열에서의 위치
	LIST* pre_list;				// 이중 리스트를 활용하여 값을 옮길 시 사용
} WORLD_NODE;

typedef struct _WORLD_ {
	int width, height;
	LIST*** world;		// LIST*** : 2-D Array + LIST*
} WORLD;

VEC2 	world_where 	( VEC2 pos );	// 배열상에 저장될 위치를 계산

// -- allocate and release world

void 	world_init		( WORLD* _world, int _x_size, int _y_size );
void 	resize_world		( WORLD* _world, int _x_size, int _y_size );
void 	world_release 	( WORLD* _world );	// world 전체를 해제

// -- set world

int 	world_insert 		( WORLD* _world, VEC2 where, void* elem, int index );

void 	world_update		( WORLD* _world, int section_x, int section_y,
						  	  void (*update)(void* elem, VEC2* get_pos));
				// world_node 하나를 해제

#endif /* WORLD_H */

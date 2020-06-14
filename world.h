#ifndef WORLD_H
#define WORLD_H

#include "hash_table.h"
#include "vector2.h"

#define __WORLD_UNIT 10000
#define __WORLD_HOW_MUCH_UNIT 100
#define __WORLD_SIZE __WORLD_UNIT*__WORLD_HOW_MUCH_UNIT

#define create_world(_size) 	LIST* _title[_size][_size];\
								init_map(_title, _size);

#define create_world_oblong(_x_size, _y_size) 	LIST* _title[_x_size][_y_size];\
												world_init(_title, _x_size, _y_size);

typedef struct _WORLD_NODE_ {
	void* elem;					// 물체를 저장하고있는 메모리의 위치
	int index;					// g_object 등 해당 배열에서의 위치
	LIST* pre_list;				// 이중 리스트를 활용하여 값을 옮길 시 사용
} WORLD_NODE;

typedef LIST*** WORLD;			// 2차원 배열 + LIST

VEC2 	world_where 	( VEC2 pos );	// 배열상에 저장될 위치를 계산

void 	world_init 		( WORLD world, int x_size, int y_size );	// world를 초기화\

int 	world_insert 	( WORLD world, int size_x, int size_y,		// world에 요소를 추가
						  int x, int y, void* elem, int index );

void 	world_update	( WORLD world, int section_x, int section_y,
						  void (*update)(void* elem, VEC2* get_pos));

void 	world_release_node ( void* target );						// world_node 하나를 해제
void 	world_release 	( WORLD world, int x_size, int y_size );	// world 전체를 해제

#endif /* WORLD_H */

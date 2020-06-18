#ifndef WORLD_H
#define WORLD_H

#include "hash_table.h"

#include "vector2.h"

#define __WORLD_UNIT 100
#define __WORLD_EARLY_SIZE 100
#define __WORLD_SIZE __WORLD_UNIT*__WORLD_HOW_MUCH_UNIT
#define str(x) #x

// ------------------------------------------------------- //
// ----- Quadrant 		-----------------------------------

typedef enum __QUADRANT_NUM__ {		// 2차원 좌표계의 사분면을 표현
	__QUADRANT_1 = 1 << 0,
	__QUADRANT_2 = 1 << 1,
	__QUADRANT_3 = 1 << 3,
	__QUADRANT_4 = 1 << 4,
} _QUADRANT_NUM_;

/*
 *		[0] : Quadrant 1  / x -> (+) / y -> (+) /
 *		[1] : Quadrant 2  / x -> (-) / y -> (+) /
 *		[2] : Quadrant 3  / x -> (-) / y -> (-) /
 *		[3] : Quadrant 4  / x -> (+) / y -> (-) /
 */

typedef struct _QUADRANT_ {
	LIST* part[4];
} QUADRANT;

// ------------------------------------------------------- //
// ----- World 		---------------------------------------

/*
 *		게임 내의 일정 단위로 구역을 정하고 일정 구역 안에 있는 객체들을 한대 묶어 저장
 *		이는 매 프레임 모든 물체들을 업데이트하면 물체의 갯수가 많아질수록 게임이 차지하는
 *		자원이 커지기 때문에 이를 방지하기 위해 일정 구역의 물체만 업데이트하기 위함.
 */

typedef struct _WORLD_NODE_ {
	void* elem;					// 물체를 저장하고있는 메모리의 위치
	int index;					// g_object 등 해당 배열에서의 위치
	LIST* pre_list;				// 이중 리스트를 활용하여 값을 옮길 시 사용
} WORLD_NODE;

typedef struct _WORLD_ {
	int width;					// 객체의 좌표값을 절대값으로 변환하여
	int height;				// +가 된 좌표값에 해당하는 배열 위치 QUADRANT
	QUADRANT** world;		// 구조체에 값을 저장한다.
} WORLD;

VEC2 	world_where 	( VEC2 pos );	// 배열상에 저장될 위치를 계산

// ------------------------------------------------------- //
// ----- Quadrant functions		--------------------------

void 	quadrant_init 		( QUADRANT* target );
void 	quadrant_release 	( QUADRANT* target );
int 	quadrant_is_exist 	( QUADRANT* target );		// return quadrant bit flag

int		quadrant_get_index	( VEC2 pos );

// ------------------------------------------------------- //
// ----- world functions		-----------------------------

// -- allocate and release world

void 	world_init		( WORLD* _world, int _x_size, int _y_size );		// world 를 초기화
void 	resize_world		( WORLD* _world, int _x_size, int _y_size );	// world 의 크기를 늘려줌
void 	world_release 	( WORLD* _world );									// world 전체를 해제

void	world_node_free	( void* node );		// world 노드 하나를 해제

// -- set world

int 	world_insert 		( WORLD* _world, VEC2 where, void* elem, int index );

void 	world_update		( WORLD* _world, int section_x, int section_y,
						  	  void (*update)(void* elem, VEC2* get_pos));

#endif /* WORLD_H */

#include "world.h"

VEC2 world_where ( VEC2 pos ) {
	VEC2 result = vec2_div(&pos, __WORLD_UNIT);
	
	result.x = fabs(result.x);
	result.y = fabs(result.y);
	
	result.x = floor(result.x);
	result.y = floor(result.y);
	
	return result;
}

// ------------------------------------------------------- //
// ----- Quadrant functions		--------------------------

void quadrant_init ( QUADRANT* target ) {
	(target->part)[0] = NULL;
	(target->part)[1] = NULL;
	(target->part)[2] = NULL;
	(target->part)[3] = NULL;
}

void quadrant_release ( QUADRANT* target ) {
	if( (target->part)[0] != NULL )
		list_release( (target->part)[0], world_node_free );
	
	if( (target->part)[1] != NULL )
		list_release( (target->part)[1], world_node_free );
	
	if( (target->part)[2] != NULL )
		list_release( (target->part)[2], world_node_free );
	
	if( (target->part)[3] != NULL )
		list_release( (target->part)[3], world_node_free );
}

int quadrant_is_exist ( QUADRANT* target ) {
	int flag = 0;
	
	if( (target->part)[0] != NULL )
		flag |= __QUADRANT_1;
	
	if( (target->part)[1] != NULL )
		flag |= __QUADRANT_2;
	
	if( (target->part)[2] != NULL )
		flag |= __QUADRANT_3;
	
	if( (target->part)[3] != NULL )
		flag |= __QUADRANT_4;
	
	return flag;
}

int	 quadrant_get_index ( VEC2 pos ) {
	int index = 0;
	
	if(pos.x < 0) {
		if(pos.y < 0)
			index = 2;		// (x : (-)), (y : (-))  = 2
		else
			index = 1;		// (x : (-)), (y : (+))  = 1
	}
	else {
		if(pos.y < 0)
			index = 3;		// (x : (+)), (y : (-))  = 3
		else
			index = 0;		// (x : (+)), (y : (+))  = 0
	}
	
	return index;
}

// ------------------------------------------------------- //
// ----- world functions		-----------------------------

// -- create and release

void world_init ( WORLD* _world, int _x_size, int _y_size ) {
	int i = 0, j = 0;

	_world->width = _x_size;
	_world->height = _y_size;
	
	_world->world = (QUADRANT**) malloc (sizeof(QUADRANT*) * _x_size);
	
	for(i = 0; i < _x_size; i++) {
		(_world->world)[i] = (QUADRANT*) malloc (sizeof(QUADRANT) * _y_size);
		
		for( j = 0; j < _y_size; j++ ) {
			quadrant_init( &(_world->world)[i][j] );	// 새로 할당된 메모리를 초기화
		}
	}
	
}

void resize_world ( WORLD* _world, int _x_size, int _y_size ) {
	int i = 0, j = 0;
	
	if( _world->width > _x_size || _world->height > _y_size )
		return;
	
	// world 의 가로 크기를 늘려줌
	_world->world = ( QUADRANT** ) realloc ( _world->world[i], sizeof(QUADRANT*)*_x_size );
	
	// world 의 세로 크기를 늘려줌
	for( i = 0; i < _x_size; i++) {
		_world->world[i] = ( QUADRANT* ) realloc ( _world->world[i], sizeof(QUADRANT)*_y_size );
		
		for( j = _world->height; j < _y_size; j++ ) {
			quadrant_init( &((_world->world)[i][j]) );	// 새로 할당된 메모리를 초기화
		}
	}
	
	_world->width 		= _x_size;
	_world->height 	= _y_size;
}

void world_release ( WORLD* _world ) {
	int i = 0, j = 0;
	
	for( i = 0; i < _world->width; i++ ) {
		
		for( j = 0; j < _world->height; j++ )
			quadrant_release( &( _world->world[i][j] ) );		// 안에 저장된 요소들을 해제
		
		free( _world->world[i] );
	}
	
	free( _world->world );
}

void world_node_free ( void* node ) {
	free(node);
}

int world_insert ( WORLD* _world, VEC2 where, void* elem, int index  ) {
	int quadrant_index = 0;
	LIST** target;
	LIST* inserter_l = NULL;
	WORLD_NODE* inserter_w = NULL;
	
	if ( (where.x < 0 && where.x >= __WORLD_UNIT * _world->width) ||
		  (where.y < 0 && where.y >= __WORLD_UNIT * _world->height) ) {
		
		return -1;
	}
	
	quadrant_index = quadrant_get_index(where);
	
	where = world_where( where );
	
	inserter_w = (WORLD_NODE*) malloc (sizeof(WORLD_NODE));
	inserter_w->index = index;
	inserter_w->elem = elem;
	
	inserter_l = list_create(inserter_w);
	
	target = _world->world[(int)where.x][(int)where.y].part;
	if( target[quadrant_index] != NULL )
		((WORLD_NODE*)((target[quadrant_index])->elem))->pre_list = inserter_l;
	
	target[quadrant_index] = list_push_front ( target[quadrant_index], inserter_l );
	
	return 0;
}

void world_update ( WORLD* _world, int section_x, int section_y,
					    void (*update)(void* elem, VEC2* get_pos)) {
	WORLD_NODE* elem = NULL;
	VEC2 elem_pos = V2_ZERO;
	LIST** first_node = NULL;
	LIST** new_quadrant = NULL;
	LIST* node = NULL;
	int quadrant_index = quadrant_get_index( (VEC2){section_x, section_y} );
	
	first_node = _world->world[section_x][section_y].part;
	node = first_node[quadrant_index];
	
	printf("update : (%d, %d)[%d] : list ptr : %p \n", section_x, section_y, quadrant_index, first_node);
	
	while(node != NULL) {
		elem = node->elem;						// 리스트에 저장된 요소를 가져옴
		
		update(elem->elem, &elem_pos);			// 해당 요소를 업데이트
		
		elem_pos = world_where(elem_pos);		// 해당 요소가 자리해야할 구역을 계산
		
		// -- 해당 구역을 넘어갔을 경우 --
		if ( (int)elem_pos.x != section_x || (int)elem_pos.y != section_y ) {
		
			// 해당 구역의 list 순서를 업데이트
			if(elem->pre_list == NULL) {			// 첫번째 노드일 경우
				first_node[quadrant_index] = node->next;			// 시작점 노드를 다음 노드로 변경
			}
			else {										// 첫번째가 아닐 경우
				elem->pre_list->next = node->next;	// 이전 노드의 다음 포인터를 다다음으로 변경
				
				if( node->next != NULL )				// 다음 노드가 존재 시
					((WORLD_NODE*)(node->next->elem))->pre_list = elem->pre_list;
			}
			
			node->next = NULL;
			
			printf("\n\nworld : %d, %d \n\n", ((int)elem_pos.x), ((int)elem_pos.y));
			
			// 해당 요소의 구역을 바꾸어줌
			quadrant_index = quadrant_get_index( elem_pos );
			new_quadrant = _world->world[(int)elem_pos.x][(int)elem_pos.y].part;
			
			if( new_quadrant[quadrant_index] != NULL )
				((WORLD_NODE*)((new_quadrant[quadrant_index])->elem))->pre_list = node;
			
			new_quadrant[quadrant_index] = list_push_front ( new_quadrant[quadrant_index], node );
		}

		node = node->next;		// 다음 리스트 업데이트 진행
	}
}

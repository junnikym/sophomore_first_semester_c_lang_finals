#include "world.h"

VEC2 world_where ( VEC2 pos ) {
	VEC2 result = vec2_div(&pos, __WORLD_UNIT);
	
	result.x = floor(result.x);
	result.y = floor(result.y);
	
	return result;
}

// -- create and release

void world_init ( WORLD* _world, int _x_size, int _y_size ) {
	int i = 0, j = 0;
	
	_world->width = _x_size;
	_world->height = _y_size;
	
	_world->world = (LIST***) malloc (sizeof(LIST**) * _x_size);
	
	for(i = 0; i < _x_size; i++) {
		(_world->world)[i] = (LIST**) malloc (sizeof(LIST*) * _y_size);
		
		for( j = 0; j < _y_size; j++ ) {
			_world->world[i][j] = NULL;	// 새로 할당된 메모리의 LIST*를 NULL로 초기화
		}
	}
}

void resize_world ( WORLD* _world, int _x_size, int _y_size ) {
	int i = 0, j = 0;
	
	if( _world->width > _x_size || _world->height > _y_size )
		return;
	
	// world 의 가로 크기를 늘려줌
	_world->world = ( LIST*** ) realloc ( _world->world[i], sizeof(LIST**)*_x_size );
	
	// world 의 세로 크기를 늘려줌
	for( i = 0; i < _x_size; i++) {
		_world->world[i] = ( LIST** ) realloc ( _world->world[i], sizeof(LIST**)*_y_size );
		
		for( j = _world->height; j < _y_size; j++ ) {
			_world->world[i][j] = NULL;	// 새로 할당된 메모리의 LIST*를 NULL로 초기화
		}
	}
	
	_world->width 		= _x_size;
	_world->height 	= _y_size;
}

void world_release ( WORLD* _world ) {
	int i = 0, j = 0;
	
	for( i = 0; i < _world->width; i++ ) {
		
		for( j = 0; j < _world->height; j++ ) {
			
			if( _world->world[i][j] != NULL ) {
				
				// world 를 해제 할 때는 world_node만 해제 - 안의 내용물의 메모리는 따로 해제
				list_release( _world->world[i][j], free);
			}
			
		}
		
		free( _world->world[i] );
	}
	
	free( _world->world );
}

int world_insert ( WORLD* _world, VEC2 where, void* elem, int index  ) {
	LIST* inserter_l = NULL;
	WORLD_NODE* inserter_w = NULL;
	WORLD_NODE* current = NULL;
	
	if ( (where.x < 0 && where.x >= __WORLD_UNIT * _world->width) ||
		  (where.y < 0 && where.y >= __WORLD_UNIT * _world->height) ) {
		
		return -1;
	}
	
	where = world_where( where );
	inserter_w = (WORLD_NODE*)malloc(sizeof(WORLD_NODE));
	
	inserter_w->index = index;
	inserter_w->elem = elem;
	
	inserter_l = list_create(inserter_w);
	
	if( _world->world[(int)where.x][(int)where.y] != NULL ) {
		current = ( _world->world[(int)where.x][(int)where.y] )->elem;
		current->pre_list = inserter_l;
	}
	
	_world->world[(int)where.x][(int)where.y] = list_push_front (
													  _world->world[(int)where.x][(int)where.y],
													  inserter_l
												  );
	
	return 0;
}

void world_update ( WORLD* _world, int section_x, int section_y,
					    void (*update)(void* elem, VEC2* get_pos)) {
	WORLD_NODE* elem = NULL;
	VEC2 elem_pos = V2_ZERO;
	LIST* node = _world->world[section_x][section_y];

	while(node != NULL) {
		elem = node->elem;						// 리스트에 저장된 요소를 가져옴
		
		update(elem->elem, &elem_pos);			// 해당 요소를 업데이트
		
		elem_pos = world_where(elem_pos);		// 해당 요소가 자리해야할 구역을 계산
		
		// -- 해당 구역을 넘어갔을 경우 --
		if ( elem_pos.x != section_x || elem_pos.y != section_y ) {
		
			// 해당 구역의 list 순서를 업데이트
			if(elem->pre_list == NULL) {
				_world->world[(int)elem_pos.x][(int)elem_pos.y] = node->next;
			}
			else {
				elem->pre_list->next = node->next;
				
				if(node->next != NULL)
					((WORLD_NODE*)(node->next->elem))->pre_list = elem->pre_list;
			}
			
			node->next = NULL;
			
			printf("\n\nworld : %d, %d \n\n", (int)elem_pos.x, (int)elem_pos.y);
			printf("\n\nworld : %d, %d \n\n", ((int)elem_pos.x), ((int)elem_pos.y));
			
			// ! TODO : (-) -> error // make to (-) -> (+)
			
			// 해당 요소의 구역을 바꾸어줌
			_world->world[(int)elem_pos.x][(int)elem_pos.y] =
												list_push_front (
													_world->world[(int)elem_pos.x][(int)elem_pos.y],
													node
												);
		}

		node = node->next;		// 다음 리스트 업데이트 진행
	}
}

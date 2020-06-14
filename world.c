#include "world.h"

VEC2 world_where ( VEC2 pos ) {
	VEC2 result = vec2_div(&pos, __WORLD_UNIT);
	
	result.x = floor(result.x);
	result.y = floor(result.y);
	
	return result;
}

int world_insert ( WORLD world, int size_x, int size_y,  int x, int y, void* elem, int index ) {
	LIST* inserter_l = NULL;
	WORLD_NODE* inserter_w = NULL;
	WORLD_NODE* current = NULL;
	VEC2 where = V2_ZERO;
	
	if ( (x < 0 && x >= __WORLD_UNIT * size_x) ||
		 (y < 0 && y >= __WORLD_UNIT * size_y) ) {
		
		return -1;
	}
	
	where = world_where( (VEC2){x, y} );
	inserter_w = (WORLD_NODE*)malloc(sizeof(WORLD_NODE));
	
	inserter_w->index = index;
	inserter_w->elem = elem;
	
	inserter_l = list_create(inserter_w);
	
	if( world[(int)where.x][(int)where.y] != NULL ) {
		current = world[(int)where.x][(int)where.y]->elem;
		current->pre_list = inserter_l;
	}
	
	world[(int)where.x][(int)where.y] =	list_push_front (
											world[(int)where.x][(int)where.y],
											inserter_l
								 		);
	
	return 0;
}

void world_update ( WORLD world, int section_x, int section_y,
					void (*update)(void* elem, VEC2* get_pos)) {
	WORLD_NODE* elem = NULL;
	VEC2 elem_pos = V2_ZERO;
	LIST* node = world[section_x][section_y];

	while(node != NULL) {
		elem = node->elem;
		
		update(elem->elem, &elem_pos);
		
		elem_pos = world_where(elem_pos);
		if ( elem_pos.x != section_x || elem_pos.y != section_y ) {
		
			// 해당 구역의 list 순서를 업데이트
			if(elem->pre_list == NULL) {
				world[(int)elem_pos.x][(int)elem_pos.y] = node->next;
			}
			else {
				elem->pre_list->next = node->next;
				
				if(node->next != NULL)
					((WORLD_NODE*)(node->next->elem))->pre_list = elem->pre_list;
			}
			
			node->next = NULL;
			
			// 해당 요소의 구역을 바꾸어줌
			world[(int)elem_pos.x][(int)elem_pos.y] =
											list_push_front (
												world[(int)elem_pos.x][(int)elem_pos.y],
												node
											);
		}

		node = node->next;
	}
}

void world_init(WORLD world, int x_size, int y_size) {
	int i = 0;

	for( i = 0; i < x_size; i++ ) {
		hash_table_init (world[i], y_size);
	}
}

void world_release_node ( void* target ) {
	free(target);
}

void world_release ( WORLD world, int x_size, int y_size ) {
	int i = 0;

	for( i = 0; i < x_size; i++ ) {
		hash_table_release(world, y_size, world_release_node);
	}
}

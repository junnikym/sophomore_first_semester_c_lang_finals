#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _LIST LIST;

struct _LIST {
	void* elem;		// 이번 순서의 리스트에 저장될 데이터
	LIST* next;		// 다음 순서의 리스트
};

LIST* 	list_create 		( void* elem );										// list를 하나 생성해주는 함수
void 	list_init			( LIST* p_list );									// list를 초기화 해주는 함수

LIST* 	list_push_front 	( LIST* p_list, LIST* p_new_list );					// list의 앞에 요소를 추가
LIST* 	list_push_back 		( LIST* p_list, LIST* p_new_list );					// list의 뒤에 요소를 추가
LIST* 	list_insert			( LIST* p_list, LIST* p_new_list, int i);			// 리스트의 중간에 요소를 추가

LIST*	list_get			( LIST* p_list, int i );							// i번째 리스트를 반환
int		list_get_size		( LIST* p_list );									// list의 크기를 반환

LIST*	list_delete			( LIST* p_list, int i );							// 중간 요소를 삭제
void	list_release		( LIST* p_list, void (*release_elem)(void* elem) );	// 리스트 전체의 메모리 해제

// 리스트 처음부터 끝까지 각 요소들을 인자로 들어온 함수 포인터에 전달하여 함수를 실행시켜주는 함수
void foreach_list ( LIST* p_list, void* msger, void (*func)(void* elem, int i, void* arg) );

#endif /* LIST_H */
















   

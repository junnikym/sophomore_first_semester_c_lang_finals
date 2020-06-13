#include "list.h"

LIST* create_list(void* elem) {
	LIST* new_list;

	new_list = (LIST*)malloc(sizeof(LIST));		// 리스트만큼 메모리를 할당하여
	new_list->elem = elem;							// 값을 설정해 줌
	new_list->next = NULL;		// 새로 생성된 리스트이므로 다음 list가 존재하지 않음

	return new_list;			// 생성된 리스트를 넘겨줌
}

LIST* push_front_list ( LIST* p_list, LIST* p_new_list ) {	// 리스트의 앞에 새로운 리스트를 추가
	p_new_list->next = p_list;		// 새로 들어온 리스트가 가장 앞이므로 새 리스트의 next가
									// 현재 가장 앞 리스트가 되어야 한다.
	return p_new_list;		// p_new_list가 기준이 되므로 새 리스트를 리턴해 준다.
}

LIST* push_back_list ( LIST* p_list, LIST* p_new_list ) {		// 리스트의 맨 뒤에 새 리스트를 추가
	LIST* p;

	if( p_list == NULL ) 		// 만약 p_list가 없을 경우 새 리스트를 반환
		return p_new_list;
	
	for ( p = p_list; p->next != NULL; p = p->next )
		;		// for문을 통해 반복하여 다음 리스트로 이동하여 맨 끝까지 이동
	p->next = p_new_list;	// 현재 맨 끝 리스트에 세 리스트를 추가해 줌
	return p_list;
}

LIST* get_list ( LIST* p_list, int i ) {	// i번째 리스트를 가져오는 함수
	int compare_i = 0;		// 다음 변수를 통하여 i번째인지 알아옴
	LIST* result = p_list;
	
	// compare_i를 1씩 증가시켜가며, 1 증가 할 때 마다 다음 리스트로 이동; i까지 도달 할 때 까지 진행
	for( compare_i = 0; compare_i != i; compare_i++ )
		result = result->next;
	
	return result;		// 찾아낸 값을 반환
}

int	 get_size_list ( LIST* p_list ) {		// 리스트의 총 사이즈를 알려주는 함수
	int compare_i = 0;
	
	while(p_list->next != NULL) {	// 다음 리스트가 없을 때 까지 반복하며
		compare_i++;					// 변수를 1씩 증가시킴
		p_list = p_list->next;			// 따라서 마지막에는 총 리스트 길이가 나온다
	}
	
	return compare_i;
}

// 리스트 중간에 새로운 리스트를 추가
LIST* insert_list ( LIST* p_list, LIST* p_new_list, int i ) {
	LIST* p = NULL;
	LIST* p_next = NULL;
	           
	if( i <= 0)		// i가 0보다 클 경우만 추가가 가능
		return NULL;
	
	p = get_list ( p_list, i-1 );		// i번째 바로 앞 list를 가져옴
	p_next = p->next;					// 받아온 리스트의 바로 뒤에 새로운 리스트를 넣고
	
	p->next = p_new_list;				// 원래 받아온 리스트의 뒤에 있던 리스트는
	p_new_list = p_next;				// 새로 추가된 리스트의 다음 리스트로 설정해준다.
	
	return p_list;
}

LIST* delete_list ( LIST* p_list, int i ) {	// i번째 리스트를 삭제
	LIST* p = NULL;
	LIST* p_next = NULL;
	
	if( i == 0 ) {			// 첫번째 값일 경우 리스트의 맨 앞부분을 2번째 리스트로 설정
		p = p_list->next;
		free(p_list);		// 할당된 메모리를 해제해준다.
		p_list = p;
	}
	
	p = get_list( p_list, i-1 );
	p_next = p->next->next;
	free ( p->next );
	p->next = p_next;
	
	return p_list;
}

void release_list ( LIST* p_list, void (*release_elem)(void* elem) ) {
	if(p_list->next != NULL) {
		release_list( p_list->next, release_elem );	// 다음 리스트가 존재 시
	}													// 다음 리스트를 해제시켜줌

	if(release_elem != NULL)
		release_elem(p_list->elem);		// 만약 해제시켜줄 요소가 존재한다면 해제
	
	free(p_list);	// 현 리스트를 해제
}

void foreach_list ( LIST* p_list, void* msger, void (*func)(void* elem, int i, void* arg) ) {
	int count = 0;

	for( ; p_list != NULL; p_list = p_list->next ) {
		func(p_list->elem, count++, msger);
	}
}
  

#include "dynamic_array.h"

// ------------------------------------------------------- //
// ----- dyn_arr functions	------------------------------

void dyn_arr_init( DYN_ARR* a, int type_size ) {	// DYN_ARR을 초기화시켜주는 함수
	a->type_size = type_size;							// 배열에 사용될 자료형의 크기
	a->capacity	= __VECTOR_INIT_CAPPACITY;		// 초기 DYN_ARR의 크기
	a->size		= -1;									// 아무 요소가 들어오지 않은 경우 -1
	a->items	= malloc(type_size * a->capacity);	// item에 먼저 초기 크기만큼 메모리를 할당
}

int dyn_arr_size( const DYN_ARR* a ) {	// 배열의 크기를 알려주는 함수
	return a->size;
}

void dyn_arr_resize( DYN_ARR* a, int capacity ) {		// 메모리를 확장하는 함수
	void* items = realloc(a->items, a->type_size * capacity);	// 메모리를 원하는 크기만큼 재할당
	if(items == NULL) {
		/* ! TODO : Error Code */
		return;
	}

	a->items = items;			// 변경된 내용을 업데이트
	a->capacity = capacity;
}

void* dyn_arr_push_back ( DYN_ARR* a, const void* elem,				// 요소를 맨 뒤에 추가하는 함수
							   void (*copy__)(void*, const void*) ) {
	void* lhs = NULL;

	a->size++;		// 요소가 추가되었으므로 size를 늘려준다.

	if(a->capacity == a->size)		// capacity와 size의 크기가 같으면 메모리가 꽉 찼다는 뜻이므로
		dyn_arr_resize( a, a->capacity * 2 );		// 기존 사이즈의 2배 만큼 늘려준다.
	
	// 1byte단위(char*)로 배열 시작 주소로부터 (자료형 사이즈) * (index) 만큼 뒤의 주소에 값을 복사해준다.
	lhs = ((char*)(a->items) + (a->type_size * a->size));
	copy__( lhs, elem );

	return lhs;
}

void* dyn_arr_insert( DYN_ARR* a, int index, void* elem,			// 배열 중간의 값을 변경해주는 함수
					 	  void (*copy__)(void*, const void*) ) {
	void* target = ((char*)(a->items) + (a->type_size * index));	// 변경할 자리의 주소값을 계산
	
	if(index >= 0 && index <= a->size) {	// 만약 범위 안이라면 값을 복사
		copy__( target, elem );
	
		return target;
	}
	   
	return NULL;	// 실패 시 NULL 반환
}
  
void* dyn_arr_get( const DYN_ARR* a, int index ) {	// i번째 요소를 반환해줌
	void* addr = ((char*)(a->items) + (a->type_size * index));

	if(index >= 0 && index <= a->size) 
		return addr;

	return NULL;		// 범위를 벗어날 경우 NULL 리턴
}

void* dyn_arr_back( const DYN_ARR* a ) {		// 맨 마지막 요소를 리턴해 줌
	return ((char*)(a->items) + (a->type_size * a->size));
}

void dyn_arr_delete( DYN_ARR* a, int index,					// i번째 요소를 삭제
						 void (*copy__)(void*, const void*) ) {
	int i = 0;
	void* i_ptr = NULL;
	
	if( (index < 0) || (index > a->size) )		// 범위를 벗어날 경우 함수를 종료
		return;	

	for(i = 0; i < a->size; i++) {				// 비워진 자리만큼 앞으로 당겨짐
		i_ptr = ((char*)(a->items) + (a->type_size * i));
		copy__( i_ptr, (char*)i_ptr + a->type_size );
	}
	a->size--;		// 사이즈를 1 줄여줌

	if( (a->size > 0) && (a->size == a->capacity / 4) ) // 만약 사이즈가 많이 줄어든다면
		dyn_arr_resize(a, a->capacity / 2);			// 메모리를 다시 줄여 재할당해줌.
}

void dyn_arr_release( DYN_ARR* a) {
	free(a->items);	// item에 할당된 메모리를 해제
	a->items = NULL;
}

void dyn_arr_foreach ( DYN_ARR* a, void* msger,
						   void (*func)(void* elem, int i, void* arg) ) {
	int i = 0;
	for( i = 0; i <= a->size; i++ ) {			// 처음부터 끝가지 반복하며 인자로들어온 함수에
		func(dyn_arr_get(a, i), i, msger);	// 해당 요소를 삽입하여 실행시켜줌
	}
}

// ------------------------------------------------------- //
 

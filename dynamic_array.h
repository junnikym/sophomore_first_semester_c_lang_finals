#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>

#include <stdio.h>

#define __VECTOR_INIT_CAPPACITY 4;

typedef struct _DYNAMIC_ARRAY {
    void* items;
    int capacity;
    int size;

    int type_size;
} DYN_ARR;

// ------------------------------------------------------- //
// ----- dyn_arr functions	------------------------------ 

void        dyn_arr_init        	( DYN_ARR* a, int type_size );	// DYN_ARR 구조체 초기화 함수
int         dyn_arr_size        	( const DYN_ARR* a );				// DYN_ARR 의 현제 사이즈를 가져옴
void 		dyn_arr_resize      	( DYN_ARR* a, int capacity );		// 배열의 사이즈를 늘려줌
// DYN_ARR 맨 뒤에 요소를 추가함 단, void*로 요소를 표현하기 때문에 copy함수는 따로 제작하여 사용
void*       dyn_arr_push_back 	( DYN_ARR* a, const void* elem,
									  void (*copy__)(void*, const void*) );
void*       dyn_arr_insert		( DYN_ARR* a, int index, void* elem,		// DYN_ARR 중간에 요소를 추가
									  void (*copy__)(void*, const void*) );
void*       dyn_arr_get         ( const DYN_ARR* a, int index );		// i번째 요소를 반환하는 함수
void*       dyn_arr_back       	( const DYN_ARR* a );					// 맨 마지막 요소를 반환하는 함수
void        dyn_arr_delete      ( DYN_ARR* a, int index,				// i번째 요소를 지우는 함수
								      void (*copy__)(void*, const void*) );
void        dyn_arr_release     ( DYN_ARR* a);					// DYN_ARR 를 해제해주는 함수

// 배열의 첫번째부터 맨 마지막 요소까지 함수포인터로 들어온 함수의 인자에 넘겨주며 일일이 실행시켜주는 함수.
void        dyn_arr_foreach     ( DYN_ARR* a, void* msger,
								 	   void (*func)(void* elem, int i, void* arg) );

// ------------------------------------------------------- //

#endif




#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define __HASH_MULTIPLIER 31

#include "list.h"

#include <string.h>

/*		
 *		많은 량의 검색가능한 데이터를 저장해야 할 때 사용.
 *		배열에 리스트를 활용하여 충돌을 막은 체이닝 해시 테이블 방식을 사용
 */

// 해시테이블은 사이즈가 정적으로 설정이 되어야 하기 때문에 메크로 함수를 통해
// 정해진 자료형으로 원하는 사이즈만큼의 배열을 선언하고 초기화까지 할 수 있도록 함.

#define create_hash_table(_title, _size) 	LIST* _title[_size];\
											hash_table_init(_title, _size);

typedef struct _HASH_TABLE_NODE {
	char*	key;		// key를 통해 검색
	int 	hash_value;	// key를 통해 생성된 값 -> 이 값을 통해 해당 배열 위치에 저장
	void*	item;		// 저장할 데이터 
} HASH_TABLE_NODE;

typedef LIST** HASH_TABLE;	// first ptr	: for allocate memeory
							// seconde ptr	: for beginning listss

// ------------------------------------------------------- //
// ----- hash functions				----------------------

unsigned int hash ( char* str, int table_size );

unsigned int int_hash (int a, int table_size);

LIST* hash_table_find 				( HASH_TABLE table, char* _key, void* _item,
								  int table_size, int create );				// 해쉬를 통해 검색

void hash_table_init 			( HASH_TABLE table, int table_size );		// 해쉬 테이블을 초기화
void hash_table_release 		( HASH_TABLE table,							// 해쉬 테이블을 해제
							 	  int table_size, void (*release_item)(void* target) );

// ------------------------------------------------------- //
 
#endif /* HASH_TABLE_H */









 

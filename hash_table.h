#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define __HASH_MULTIPLIER 31

#include "list.h"

#include <string.h>

#define create_hash_table(_title, _size) 	LIST* _title[_size];\
													init_hash_table(_title, _size);

typedef struct _HASH_TABLE_NODE {
	char*	key;
	int 	hash_value;
	void*	item;
} HASH_TABLE_NODE;

typedef LIST** HASH_TABLE;

// ------------------------------------------------------- //
// ----- hash functions				----------------------

unsigned int hash ( char* str, int table_size );

LIST* find_hash 				( HASH_TABLE table,
								  char* _key, int table_size, int create );	// 해쉬를 통해 검색
void init_hash_table 		( HASH_TABLE table, int table_size );		// 해쉬 테이블을 초기화
void release_hash_table 	( HASH_TABLE table,							// 해쉬 테이블을 해제
							 	  int table_size, void (*release_item)(void* target) );

// ------------------------------------------------------- //
 
#endif /* HASH_TABLE_H */









 

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define __HASH_MULTIPLIER 31

#include "list.h"

#include <string.h>

#define create_hash_table(_title, _size) 	LIST* _title[_size];\
											hash_table_init(_title, _size);

typedef struct _HASH_TABLE_NODE {
	char*	key;
	int 	hash_value;
	void*	item;
} HASH_TABLE_NODE;

typedef LIST** HASH_TABLE;	// first ptr : for allocate memeory
							// seconde ptr : for beginning listss

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









 

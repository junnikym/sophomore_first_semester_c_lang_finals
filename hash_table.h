#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define __HASH_MULTIPLIER 31

#include "dynamic_array.h"
#include "list.h"

#include <string.h>

typedef struct _HASH_TABLE_NODE {
	char*	key;
	int 	hash_value;
	void*	item;
} HASH_TABLE_NODE;

typedef LIST** HASH_TABLE;

unsigned int hash ( char* str, int hash_map_size );

LIST* find_hash ( HASH_TABLE list, char* _key, int hash_map_size );


#endif /* HASH_TABLE_H */

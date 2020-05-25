#include "hash_table.h"

// ------------------------------------------------------- //
// ----- hash functions				----------------------

unsigned int hash(char* str, int hash_map_size) {
	unsigned int h = 0;
	unsigned char* p = NULL;
	
	for(p = (unsigned char *) str; *p != '\0'; p++)
		h = __HASH_MULTIPLIER * h + *p;
	
	return h % hash_map_size;
}

LIST* find_hash ( HASH_TABLE list, char* _key, int hash_map_size ) {
	unsigned int h = 0;
	LIST* node = NULL;
	
	h = hash(_key, hash_map_size);
	for(node = list[h]; node != NULL; node = node->next) {
		if ( strcmp( _key, ((HASH_TABLE_NODE*)node->elem)->key ) == 0 )
			return node;
	}
	
	return NULL;
}

// ------------------------------------------------------- //

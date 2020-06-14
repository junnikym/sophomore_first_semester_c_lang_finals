#include "hash_table.h"

// ------------------------------------------------------- //
// ----- hash functions				----------------------

unsigned int hash(char* str, int table_size) {
	unsigned int h = 0;			// 해쉬값을 저장할 변수
	unsigned char* p = NULL;
	
	for(p = (unsigned char *) str; *p != '\0'; p++)
		h = __HASH_MULTIPLIER * h + *p;	
	
	return h % table_size;
}

LIST* hash_talbe_find ( HASH_TABLE table, char* _key, void* _item, int table_size, int create ) {
	unsigned int h = 0;
	LIST* node = NULL;
	HASH_TABLE_NODE* inserter = NULL;
	
	h = hash(_key, table_size);
	node = table[h];
	
	for(node = table[h]; node != NULL; node = node->next) {
		if ( strcmp( _key, ((HASH_TABLE_NODE*)node->elem)->key ) == 0 )
			return node;
	}

	if ( create ) {
		inserter = (HASH_TABLE_NODE*)malloc(sizeof(HASH_TABLE_NODE));

		inserter->key 			= _key;
		inserter->item			= _item;
		inserter->hash_value 	= h;

		node = list_create(inserter);
		node->next = table[h];
		table[h] = node;

		return node;
	}

	return NULL;
}

void hash_table_init ( HASH_TABLE table, int table_size ) {
	int i = 0;

	for( i = 0; i < table_size; i++ ) {
		table[i] = NULL;
	}
}

void hash_table_release ( HASH_TABLE table, int table_size, void (*release_item)(void* target) ) {
	int i = 0;

	for( i = 0; i < table_size; i++ ) {
		if(table[i] != NULL) 
			list_release( table[i], release_item );
	}
}

// ------------------------------------------------------- //

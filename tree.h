#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _TREE_ TREE;

struct _TREE_ {
	char* key;
	void* value;
	TREE* left;
	TREE* right;
};

TREE* 	tree_insert		( TREE* tree, TREE* rhs );
TREE* 	tree_search		( TREE* tree, char* key );
TREE* 	tree_search_nr	( TREE* tree, char* key );	// non-recursive

// 	foreach_in 		= in-order traversal
// 	foreach_post 	= post-order traversal
void	tree_foreach_in 	( TREE* tree, void* msger, 
							  void (func)(TREE* tree, void* arg) );

void	tree_foreach_post 	( TREE* tree, void* msger, 
							  void (func)(TREE* tree, void* arg) );

#endif /* MAP_H */
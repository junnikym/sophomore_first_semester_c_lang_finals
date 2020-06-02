#include "tree.h"

TREE* tree_insert ( TREE* tree, TREE* rhs ) {
	int cmp = 0;

	if(tree == NULL) 
		return rhs;

	cmp = strcmp(rhs->key, tree->key);
	if(cmp == 0) {
		printf("ERROR : tree_insert function : 'same key' \n");
		return NULL;
	}
	else if (cmp < 0) 
		tree->left = tree_insert(tree->left, rhs);
	else 
		tree->right = tree_insert(tree->right, rhs);

	return tree;
}

TREE* tree_search ( TREE* tree, char* key ) {
	int cmp;

	if ( tree == NULL)
		return NULL;

	cmp = strcmp(key, tree->key);
	if (cmp == 0)
		return tree;
	else if (cmp < 0)
		return tree_search(tree->left, key);
	else
		return tree_search(tree->right, key);
}

TREE* tree_search_nr ( TREE* tree, char* key ) {
	int cmp;

	while (tree != NULL) {
		cmp = strcmp(key, tree->key);

		if (cmp == 0)
			return tree;

		else if (cmp < 0)
			tree = tree->left;

		else
			tree = tree->right;
	}

	return NULL;
}

void tree_foreach_in ( TREE* tree, void* msger, 
					   void (func)(TREE* tree, void* arg) ) {
	if ( tree == NULL )
		return;
	
	tree_foreach_in(tree->left, msger, func);
	(*func)(tree, msger);
	tree_foreach_in(tree->right, msger, func);
}

void tree_foreach_post ( TREE* tree, void* msger, 
						 void (func)(TREE* tree, void* arg) ) {
	if ( tree == NULL )
		return;
	
	tree_foreach_in(tree->left, msger, func);
	tree_foreach_in(tree->right, msger, func);
	(*func)(tree, msger);
}
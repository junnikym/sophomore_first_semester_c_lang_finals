#include "tree.h"

TREE* tree_create ( char* _key, void* _value ) {
	TREE* result = NULL;
	
	if( ( result = (TREE*)malloc(sizeof(TREE)) ) == NULL ) {
		return NULL;
	}
	
	result->key 	= _key;
	result->value 	= _value;
	result->right	= NULL;
	result->left	= NULL;
	
	return result;
}

TREE* tree_init ( TREE* tree ) {
	tree->key 	= NULL;
	tree->value = NULL;
	tree->right	= NULL;
	tree->left	= NULL;
	
	return tree;
}

TREE* tree_insert ( TREE* tree, TREE* rhs ) {
	int cmp = 0;

	if(tree == NULL) {
		tree = rhs;
		return rhs;
	}

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
	
	tree_foreach_post(tree->left, msger, func);
	tree_foreach_post(tree->right, msger, func);
	(*func)(tree, msger);
}

void tree_free ( TREE* tree, void* is_value_too ) {
	if( *(int*)is_value_too != 0 ) {
		free ( tree->value );
		tree->value = NULL;
	}
	
	free ( tree );
	tree = NULL;
}

void tree_release ( TREE* tree, int is_value_too ) {
	tree_foreach_post ( tree, &is_value_too, tree_free );
}

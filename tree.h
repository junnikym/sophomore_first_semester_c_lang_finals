#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _TREE_ TREE;

struct _TREE_ {
	char* key;
	void* value;
	TREE* left;		// key가 현재보다 작을 경우
	TREE* right;		// key가 현재보다 클 경우
};

TREE*	tree_create		( char* _key, void* _value );		// tree를 생성

TREE* 	tree_insert		( TREE* tree, TREE* rhs );		// 새로운 트리를 추가
TREE* 	tree_search		( TREE* tree, char* key );		// 트리에서 key를 검색하여 값을 얻어옴
TREE* 	tree_search_nr	( TREE* tree, char* key );		// non-recursive 방식

// 	foreach_in 		= in-order traversal
// 	foreach_post 	= post-order traversal
void	tree_foreach_in 	( TREE* tree, void* msger, 
							  void (func)(TREE* tree, void* arg) );

void	tree_foreach_post 	( TREE* tree, void* msger, 
							  void (func)(TREE* tree, void* arg) );

void tree_free ( TREE* tree, void* is_value_too );		// 트리 하나에 할당된 메모리를 해제
void tree_release ( TREE* tree, int is_value_too );	// 트리 전체의 메모리를 헤제

#endif /* MAP_H */










   

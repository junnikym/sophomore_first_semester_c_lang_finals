#include "tree.h"

TREE* tree_create ( char* _key, void* _value ) {		// 새로운 트리 요소 생성
	TREE* result = NULL;
	
	// 트리 메모리를 생성
	if( ( result = (TREE*)malloc(sizeof(TREE)) ) == NULL ) {
		return NULL;
	}
	
	result->key 	= _key;		// 값을 설정 및 초기화 후 반환
	result->value 	= _value;
	result->right	= NULL;
	result->left	= NULL;
	
	return result;
}

TREE* tree_init ( TREE* tree ) {		// Tree를 초기화 해주는 함수
	tree->key 	= NULL;
	tree->value = NULL;
	tree->right	= NULL;
	tree->left	= NULL;
	
	return tree;
}

TREE* tree_insert ( TREE* tree, TREE* rhs ) {	// Tree를 삽입하는 함수
	int cmp = 0;

	if(tree == NULL) {		// 삽입할 Tree가 없을 경우 rhs를 반환
		tree = rhs;
		return rhs;
	}

	cmp = strcmp(rhs->key, tree->key);	// key값을 비교하여
	if(cmp == 0) {							// 같을 경우 중복 오류를 출력
		printf("ERROR : tree_insert function : 'same key' \n");
		return NULL;
	}
	else if (cmp < 0) 						// 작을 경우 tree의 왼쪽에
		tree->left = tree_insert(tree->left, rhs);
	else 									// 클 경우 tree의 오른쪽에
		tree->right = tree_insert(tree->right, rhs);
											// tree를 삽입한다.
	return tree;
}       

TREE* tree_search ( TREE* tree, char* key ) {
	int cmp;

	if ( tree == NULL)
		return NULL;

	cmp = strcmp(key, tree->key);		// 삽입과 같은 방식으로
	if (cmp == 0)
		return tree;
	else if (cmp < 0)					// 작을 경우 왼쪽 키값을
		return tree_search(tree->left, key);
	else								// 클 경우 오른쪽 키값을
		return tree_search(tree->right, key);
}										// 비교하여 동일한 값이 나오면 값을 반환

TREE* tree_search_nr ( TREE* tree, char* key ) {	// 재귀함수가 아닌 검색함수
	int cmp;

	while (tree != NULL) {		// 재귀함수가 아닌 while문을 사용한다.
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

// Tree 전체 요소를 함수 포인터로 들어온 함수에 넘겨주어 실행시켜준다.
void tree_foreach_in ( TREE* tree, void* msger, 	// 중위 순회
					   void (func)(TREE* tree, void* arg) ) {
	if ( tree == NULL )
		return;
	
	tree_foreach_in(tree->left, msger, func);
	(*func)(tree, msger);
	tree_foreach_in(tree->right, msger, func);
}

void tree_foreach_post ( TREE* tree, void* msger, // 후위 순회
						 void (func)(TREE* tree, void* arg) ) {
	if ( tree == NULL )
		return;
	
	tree_foreach_post(tree->left, msger, func);
	tree_foreach_post(tree->right, msger, func);
	(*func)(tree, msger);
}

void tree_free ( TREE* tree, void* is_value_too ) {		// 트리 요소 하나의 메모리를 해제
	if( *(int*)is_value_too != 0 ) {
		free ( tree->value );
		tree->value = NULL;
	}
	
	free ( tree );
	tree = NULL;
}

void tree_release ( TREE* tree, int is_value_too ) {	// 트리 전체의 메모리를 해제
	// 자식노트 부터 진행하여야 하기때문에 후위 순회를 선택
	tree_foreach_post ( tree, &is_value_too, tree_free );
}

#include "list.h"

LIST* create_list(void* elem) {
	LIST* new_list;

	new_list = (LIST*)malloc(sizeof(LIST));
	new_list->elem = elem;
	new_list->next = NULL;

	return new_list;
}

LIST* push_front_list ( LIST* p_list, LIST* p_new_list ) {
	p_new_list->next = p_list;

	return p_new_list;
}

LIST* push_back_list ( LIST* p_list, LIST* p_new_list ) {
	LIST* p;

	if( p_list == NULL ) 
		return p_new_list;
	
	for ( p = p_list; p->next != NULL; p = p->next )
		;
	p->next = p_new_list;
	return p_list;
}

LIST* get_list ( LIST* p_list, int i ) {
	int compare_i = 0;
	LIST* result = p_list;
	
	for( compare_i = 0; compare_i != i; compare_i++ )
		result = result->next;
	
	return result;
}

int	 get_size_list ( LIST* p_list ) {
	int compare_i = 0;
	
	while(p_list->next != NULL) {
		compare_i++;
		p_list = p_list->next;
	}
	
	return compare_i;
}

LIST* insert_list ( LIST* p_list, LIST* p_new_list, int i ) {
	LIST* p = NULL;
	LIST* p_next = NULL;
	
	if( i <= 0)
		return NULL;
	
	p = get_list ( p_list, i-1 );
	p_next = p->next;
	
	p->next = p_new_list;
	p_new_list = p_next;
	
	return p_list;
}

LIST* delete_list ( LIST* p_list, int i ) {
	int count = 0;
	LIST* p = NULL;
	LIST* p_next = NULL;
	
	if( i == 0 ) {
		p = p_list->next;
		free(p_list);
		p_list = p;
	}
		
	
	p = get_list( p_list, i-1 );
	p_next = p->next->next;
	free ( p->next );
	p->next = p_next;
	
	return p_list;
}

void release_list ( LIST* p_list, void (*release_elem)(void* elem) ) {
	if(p_list->next != NULL) {
		release_list( p_list->next, release_elem );
	}

	if(release_elem != NULL)
		release_elem(p_list->elem);
	
	free(p_list);
}

void foreach_list ( LIST* p_list, void* msger, void (*func)(void* elem, int i, void* arg) ) {
	int count = 0;

	for( ; p_list != NULL; p_list = p_list->next ) {
		func(p_list->elem, count++, msger);
	}
}

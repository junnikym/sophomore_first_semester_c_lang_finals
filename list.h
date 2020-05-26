#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _LIST LIST;

struct _LIST {
	void* elem;
	LIST* next;
};

LIST* 	create_list 	( void* elem );
void 	init_list		( LIST* p_list );
LIST* 	push_front_list ( LIST* p_list, LIST* p_new_list );
LIST* 	push_back_list 	( LIST* p_list, LIST* p_new_list );
LIST*	get_list		( LIST* p_list, int i );
int		get_size_list	( LIST* p_list );
LIST* 	insert_list		( LIST* p_list, LIST* p_new_list, int i);
LIST*	delete_list		( LIST* p_list, int i );
void	release_list	( LIST* p_list, void (*release_elem)(void* elem) );

void foreach_list ( LIST* p_list, void* msger, void (*func)(void* elem, int i, void* arg) );

#endif /* LIST_H */

#include "object.h"

void init_obj ( OBJECT* obj ) {
	printf("here 1 ?  \n");
	obj->entities = (DYN_ARR*)malloc(sizeof(DYN_ARR));
	printf("here 2 ?  \n");
	dyn_arr_init( obj->entities, sizeof(ENTITY) );
	
	obj->center = NULL;
	obj->direction = NULL;
} 

void copy_obj( void* lhs, const void* rhs) {
	if(rhs == NULL) 
		init_obj( (OBJECT*)rhs );
	else
		*(OBJECT*)lhs = *(OBJECT*)rhs;
}

void release_obj ( OBJECT* obj ) {
	int i = 0;
	ENTITY* ent_converter = (ENTITY*)(obj->entities->items);

	for( i = 0; i < obj->entities->capacity; i++) {
		release_ent( &ent_converter[i] );
	}

	dyn_arr_release( obj->entities );
	free( obj->entities );

	obj->center = NULL;
	obj->direction = NULL;
}

void set_center_obj( OBJECT* obj, int index ) {
	if (obj->center != NULL) {
		// !TODO : detech_center_obj();
	}

	obj->center = (ENTITY*)dyn_arr_get(obj->entities, index);
}
#ifndef OBJECT_H
#define OBJECT_H

#include "physics.h"
#include "types.h"
#include "dynamic_array.h"
#include "entity.h"

typedef struct _OBJECT_ {
	DYN_ARR entities;
	ENTITY* center;
	
	VEC2 collision_box;
	int collision_indicator;
} OBJECT;

// ------------------------------------------------------- //
// ----- object functions	------------------------------

void init_obj 		( OBJECT* obj );
void copy_obj 		( void* lhs, const void* rhs);
void release_obj 	( OBJECT* obj );

void adapt_each_f_obj ( void* elem, int i, void* pos );

void update_each_obj (void* elem, int i, void* pos);
void update_obj		( OBJECT* obj );

// -- setting function

void* 	set_center_obj		( OBJECT* obj, int index );
void 	detech_center_obj	( OBJECT* obj);

// ------------------------------------------------------- //

#endif
 








 

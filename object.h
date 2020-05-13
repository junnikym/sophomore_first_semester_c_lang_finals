#ifndef OBJECT_H
#define OBJECT_H

#include "dynamic_array.h"
#include "entity.h"

typedef struct {
	DYN_ARR entities;
	ENTITY* center;
	VEC2* direction;
} OBJECT;

// ------------------------------------------------------- //
// ----- object functions	------------------------------

void init_obj 		( OBJECT* obj );
void copy_obj 		( void* lhs, const void* rhs);
void release_obj 	( OBJECT* obj );

void adapt_each_f_obj ( void* elem, int i, void* pos );
void adapt_f_obj ( OBJECT* obj );
VEC2 pass_by_f_obj ( OBJECT* obj );

// -- setting function

void set_center_obj		( OBJECT* obj, int index );
void detech_center_obj	( OBJECT* obj);

// ------------------------------------------------------- //

#endif

#ifndef OBJECT_H
#define OBJECT_H

#include "physics.h"
#include "types.h"
#include "dynamic_array.h"
#include "entity.h"

typedef struct _BOX_ {
	VEC2 position;
	VEC2 size;
} BOX;

typedef struct _CIRCLE_ {
	VEC2 position;
	double radius;
} CIRCLE;

typedef struct _OBJECT_ {
	DYN_ARR entities;
	ENTITY* center;
	
	// -- for collision check
	DYN_ARR collision_box;		// 面倒 备开 : BOX屈
	DYN_ARR collision_circle;	// 面倒 备开 : 盔屈
	
	int collision_indicator;
	
	VEC2 head_for;
} OBJECT;


// ------------------------------------------------------- //
// ----- copy functions	--------------------------------

void copy_box ( BOX* lhs, BOX* rhs );
void copy_circle ( CIRCLE* lhs, CIRCLE* rhs );

// ------------------------------------------------------- //
// ----- object functions	--------------------------------

void	init_obj 			( OBJECT* obj );
void	copy_obj 			( void* lhs, const void* rhs);
void	release_obj 		( OBJECT* obj );

void	adapt_each_f_obj	( void* elem, int i, void* pos );

void	update_each_obj		(void* elem, int i, void* pos);
void	update_obj			( OBJECT* obj );

// -- setting function

void* 	set_center_obj		( OBJECT* obj, int index );
void 	detech_center_obj	( OBJECT* obj);

// -- collision function

int obj_is_collision ( OBJECT* lhs, OBJECT* rhs );

// ------------------------------------------------------- //


#endif
 








 

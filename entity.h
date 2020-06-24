#ifndef ENTITY_H
#define ENTITY_H

#include "force.h"
#include "dynamic_array.h"
#include "types.h"

#include "opengl/buffer_obj.h"

#define __N_ESSENTIAL_FORCE__CONTROL 2
#define __N_ESSENTIAL_FORCE__PHY 1

#define __I_ESSENTIAL_FORCE__CONTROL 0

static const int __I_ESSENTIAL_FORCE__PHY =
							__N_ESSENTIAL_FORCE__CONTROL + __I_ESSENTIAL_FORCE__CONTROL;

static const int __N_ESSENTAL_FORCE =
							__N_ESSENTIAL_FORCE__CONTROL + __N_ESSENTIAL_FORCE__PHY;

typedef struct _ENTITY {
    VEC2 position;
    double angle;
    DYN_ARR forces;   // VEC2
    // !TODO : Create attribute; (mass, meterial, ... )
	BUFFER_OBJECT* graphics_buf;
	VEC2 texture_pos; 
	double buf_z;
} ENTITY;

void init_ent       ( ENTITY* ent );
void release_ent    ( ENTITY* ent );

void copy_ent       ( void* lhs, const void* rhs );

void modify_ent(void* lhs, const void* rhs);
void modify_ent_texture_pos(void* lhs, const void* rhs);

void adapt_each_f_ent ( void* f_in_e, int i, void* pos );
void adapt_f_ent    ( ENTITY* ent );

// ! TODO : change function name -> pass_by_... -> pass_...
MOMENTUM pass_by_f_ent  ( ENTITY* ent );

void draw_ent		( const ENTITY* ent );

void set_essential_f_ent ( ENTITY* ent );

#endif
 
 

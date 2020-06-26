#ifndef ENTITY_H
#define ENTITY_H

#include "force.h"
#include "dynamic_array.h"
#include "types.h"
#include "tree.h"

#include "opengl/buffer_obj.h"

#define __N_ESSENTIAL_FORCE__CONTROL 2
#define __N_ESSENTIAL_FORCE__PHY 1

#define __I_ESSENTIAL_FORCE__CONTROL 0

static const int __I_ESSENTIAL_FORCE__PHY =
							__N_ESSENTIAL_FORCE__CONTROL + __I_ESSENTIAL_FORCE__CONTROL;

static const int __N_ESSENTAL_FORCE =
							__N_ESSENTIAL_FORCE__CONTROL + __N_ESSENTIAL_FORCE__PHY;

static int user_was_on_gournd = 0;
static int user_want_brake = 0;

typedef struct _ENTITY {
    VEC2 position;
    double angle;
    DYN_ARR forces;   // VEC2
    // !TODO : Create attribute; (mass, meterial, ... )
	BUFFER_OBJECT* graphics_buf;
	VEC2 texture_pos; 
	double buf_z;
	vec4 blend_color;
	TREE* animate;
	int is_breke;
} ENTITY;

// 엔티티를 제동을 껏다 켜줄 함수
void ent_toggle_brake(void* ent, const void* brake);		

void init_ent       ( ENTITY* ent );	// entity 초기화 함수
void release_ent    ( ENTITY* ent );	// entity 를 해제해주는 함수

// ----- 함수포인터로 전달되어 entity요소들을 변경해주는 함수들 -----
void copy_ent				( void* lhs, const void* rhs );
void modify_ent				(void* lhs, const void* rhs);
void modify_ent_texture_pos	(void* lhs, const void* rhs);
void set_blend_in_ent		(void* lhs, const void* blend);
// ------------------------------------------------------------------

// entity에 force를 적용 시키는 함수
void adapt_each_f_ent ( void* f_in_e, int i, void* pos );
void adapt_f_ent    ( ENTITY* ent );

// entity에 force를 종합하여 넘겨주는 함수
MOMENTUM pass_by_f_ent  ( ENTITY* ent );

// entity를 화면에 출력하는 함수
void draw_ent		( const ENTITY* ent );
void fixed_draw_ent	( const ENTITY* ent );

// 게임에 필요한 조작에 필요한 힘, 물리에 필요한 힘 등을 추가해주는 함수
void set_essential_f_ent ( ENTITY* ent );

#endif
 
 

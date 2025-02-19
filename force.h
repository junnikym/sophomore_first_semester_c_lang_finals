#ifndef FORCE_H
#define FORCE_H

#include "identify.h"
#include "types.h"
#include "vector2.h"
#include "dynamic_array.h"

#include <stdlib.h>
#include <math.h>

#include <GL/glew.h>

#define FORCE_INIT 		{V2_ZERO, -1, 0.0, V2_ZERO}

#define MOMENTUM_INIT 	{V2_ZERO, 0.0}

/*		[ FORCE ]
 *
 *		물체에 Force 구조체를 활용하여 물체를 시간당 원하는 만큼 움직일 수 있도록 설정
 */

// 해당 Force가 어떤 용도로 쓰이는지, 어떤 상태인지를 나타내기 위한 열거형
typedef enum __FORCE_FLAGS__ {
	__F_ACCELERATE__	= (1 << 0),		// for control
	__F_NON_FRICTION__	= (1 << 1),
	__F_PAUSE__			= (1 << 2),
	__F_ROTATE__		= (1 << 3),
	__F_FOR_CONTROL__	= (1 << 4) | __F_ACCELERATE__,
	__F_PHY_GRAVITY__	= (1 << 5) | __F_ACCELERATE__,		// for physics
	__F_BRAKE__			= (1 << 6),
} _FORCE_FALGS_;

typedef struct _FORCE {
    VEC2 force_vec;
	int identify;				// INSERT FLAGS INTO FORCE->ID
	double start_t;
	VEC2 accel_vec;			// 가속도 사용 시 쓰임
} FORCE;

// 힘이 작용된 정도를 외부로 전달하기 위해 선언된 구조체
typedef struct _MOMENTUM_ {
	VEC2 vector;
	double angle;
} MOMENTUM;

// (포인트형)
typedef struct _MOMENTUM_PTR_ {
	VEC2* vector;
	double* angle;
} MOMENTUM_PTR;

// -- setting function
void 	copy_force		(void* lhs, const void* rhs);
void	add_force		(void* lhs, const void* rhs);
void 	set_accel_in_f 	(void* f, const void* accel);
void 	set_identify_in_f (void* f, const void* id);

void 	init_force		( FORCE* f );
void 	set_vec_force	( FORCE* f, double x, double y );

// -- getter
MOMENTUM output_force 	( FORCE* force, double t );

FORCE*	search_id_force	( DYN_ARR* arr, int id );
FORCE 	generate_force	( VEC2 f, int id );

void 	toggle_force	( FORCE* target, int flag );

#endif

   

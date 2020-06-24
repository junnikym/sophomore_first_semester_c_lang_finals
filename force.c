#include "force.h"

void copy_force(void* lhs, const void* rhs) {
	FORCE* lhs_conv = lhs;
	FORCE* rhs_conv = rhs;
	
	if ( rhs == NULL ) 
		init_force( (FORCE*)lhs );
	else {
		lhs_conv->force_vec = rhs_conv->force_vec;

		if ( rhs_conv->identify != 0 ) {
			lhs_conv->identify = rhs_conv->identify;

			if ( rhs_conv->identify & (__F_ACCELERATE__ << __FORCE_ENUM_SHIFTER) ) {
				lhs_conv->accel_vec = rhs_conv->accel_vec;
			}
		}
		
		if ( lhs_conv->start_t != rhs_conv->start_t ) {
			lhs_conv->start_t = rhs_conv->start_t;
		}
	}
}

void add_force (void* lhs, const void* rhs) {
	if ( lhs == NULL || rhs == NULL )
		return;
	else {
		vec2_add_assn ( &((FORCE*)lhs)->force_vec, &((FORCE*)rhs)->force_vec );
		vec2_add_assn ( &((FORCE*)lhs)->accel_vec, &((FORCE*)rhs)->accel_vec );
	}
}

void set_accel_in_f (void* f, const void* accel) {
	if ( f == NULL || accel == NULL )
		return;
	
	else {
		((FORCE*)f)->accel_vec = *(VEC2*)accel;
	}
}

void set_identify_in_f (void* f, const void* id) {
	if ( f == NULL || id == NULL )
		return;
	
	else {
		((FORCE*)f)->identify = *(int*)id;
	}
}

void init_force( FORCE* f ) {
	*f = (FORCE)FORCE_INIT;
}

void set_vec_force( FORCE* f, double x, double y ) {
	f->force_vec.x = x;
	f->force_vec.y = y;
}

// force를 인자로 들어온 시간에 대한 force값을 계산한다.
MOMENTUM output_force ( FORCE* f, double t ) {
	MOMENTUM result = MOMENTUM_INIT;
	VEC2 vec = V2_ZERO;
	double vec_size = 0.0;
	
	// 비트 플래그에 정지 비트가 있을 경우 초기값을 반환
	if( f->identify & (__F_PAUSE__ << __FORCE_ENUM_SHIFTER) ) {
		f->start_t = 0.0;
		return (MOMENTUM)MOMENTUM_INIT;
	}

	// 만약 최초 작동시 시간이 적용되지 않았기에 시간만 작동 시켜준다.
	if ( f->start_t == 0.0 ) {
		f->start_t = t;
	}
	else {		// 시간이 적용 되어 있다면 시간에 대한 force값을 계산한다.
		
		if ( !(f->identify & __F_BRAKE__ << __FORCE_ENUM_SHIFTER) ) {

			// Force 옵션에 가속도가 설정되어 있다면 force에 적용될 벡터를 가속도만큼 증가시켜준다.
			if (f->identify & (__F_ACCELERATE__ << __FORCE_ENUM_SHIFTER)) {
				result.vector = vec2_mul(&f->accel_vec, (t - f->start_t));
				vec2_add_assn(&f->force_vec, &(result.vector));
			}

		}
		
		// -- rotational momentum -----	// 회전 운동
		
		if( f->identify & (__F_ROTATE__ << __FORCE_ENUM_SHIFTER) ){

			if (f->identify & __F_BRAKE__ << __FORCE_ENUM_SHIFTER) {
				vec2_mul_assn(&f->force_vec, 0.9);
			}

			vec_size = sqrt( SQUARE(f->force_vec.x) + SQUARE(f->force_vec.y) );
			
			if( vec_size == 0 ) {
				result.angle = 0;
			}
			else {
				if (f->force_vec.x == 0) {
					result.angle = f->force_vec.y;
				}
				else if (f->force_vec.y == 0) {
					result.angle = f->force_vec.x;
				}
				else {
					vec = vec2_normalize( f->force_vec, &vec_size );
					
					result.angle = acos(vec.x) * vec_size;
				}
			}
			
			return result;
		}
		
		// -- normal force momentum --- // 일반 힘 처리

		result.vector = vec2_mul ( &f->force_vec, (t - f->start_t) );
		f->start_t = t;
	}
	
	return result;
}

FORCE* search_id_force( DYN_ARR* arr, int id ) {
	int i = 0;
	FORCE* result = NULL;
	FORCE* converter = NULL;
	
	for(i = 0; i <= arr->size; i++) {
		converter = dyn_arr_get(arr, i);
		printf("id_on_conv : %d, id on arg : %d \n", converter->identify, id);
		
		if ( converter->identify & id ) {
			return converter;
		}
	}
	
	return result;
}

FORCE generate_force( VEC2 f, int id) {
	return (FORCE){ f, id, 0 };
}

void toggle_force ( FORCE* target, int flag ) {
	target->identify ^= flag;
}
 

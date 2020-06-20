#include "vector2.h"

// ───────────────────────────────────────────────────
// ───── VEC2 functions ──────────────────────────────

// ─── setter functions

void zeroset_coord( VEC2 x ) {
    x.x = 0;
    x.y = 0;
}

// ─── getter functions

double get_size( const VEC2* x ) {
    return sqrt( (x->x * x->x) + (x->y * x->y) );
}

// ─── arithmetic functions 

// assignment as arg
void vec2_add_assn(VEC2* target, const VEC2* rhs) {
    target->x += rhs->x;
    target->y += rhs->y;
}

void vec2_sub_assn(VEC2* target, const VEC2* rhs) {
    target->x -= rhs->x;
    target->y -= rhs->y;
}
          
void vec2_mul_assn(VEC2* target, double w) {
    target->x *= w;
    target->y *= w;
}

void vec2_div_assn(VEC2* target, double a) {
    target->x /= a;
    target->y /= a;
}


VEC2 vec2_add(const VEC2* lhs, const VEC2* rhs) {
    VEC2 result = { lhs->x + lhs->x, lhs->y + lhs->y };
    return result;
}

VEC2 vec2_sub(const VEC2* lhs, const VEC2* rhs) {
    VEC2 result = { lhs->x - lhs->x, lhs->y - lhs->y };
    return result;
}

VEC2 vec2_mul(const VEC2* target, double w) {
    VEC2 result = { target->x * w, target->y * w };
    return result;
}

VEC2 vec2_div(const VEC2* target, double a) {
    VEC2 result = { target->x / a, target->y / a };
    return result;
}

void append_array_vec2(void* arr, int index, void* elem_addr) {
    ((VEC2*)(arr))[index] = *(VEC2*)elem_addr;
}

void normalize_assn(VEC2* vec, const double* vec_size) {
    vec->x /= *vec_size;
    vec->y /= *vec_size;
}

VEC2 normalize(VEC2 vec, const double* vec_size) {
    vec.x /= *vec_size;
    vec.y /= *vec_size;

    return vec;
}

double deg_to_rad(double deg) {
	return deg * __ONE_RADIAN;
}

double vec2_dot(const VEC2* lhs, const VEC2* rhs) {
	return fabs(lhs->x * rhs->x + lhs->y * rhs->y);
}

double vec2_cross ( const VEC2* lhs, const VEC2* rhs ) {
    return lhs->x * rhs->y - lhs->y * rhs->x;
}

VEC2 vec2_get_distance ( const VEC2* lhs, const VEC2* rhs ) {
	VEC2 result;
	result.x = lhs->x - rhs->x;
	result.y = lhs->y - rhs->y;
	return result;
}

VEC2 vec2_get_height ( const VEC2* scale, const double* angle){	//height vector
	VEC2 result;
	
	result.x = scale->y * sinf( deg_to_rad(*angle) );
	result.y = scale->y * cosf( deg_to_rad(*angle) );
	
	return result;
}

VEC2 vec2_get_width ( const VEC2* scale, const double* angle){ 	//height vector
	VEC2 result;
	
	result.x = scale->x * cosf( deg_to_rad(*angle) );
	result.y = scale->x * sinf( deg_to_rad(*angle) );
	
  	return result;
}

VEC2 vec2_get_unit (const VEC2* a){ 								//unit vector
	VEC2 result;
	double size;
	
	size = sqrt(SQUARE(a->x) + SQUARE(a->y));
	
	result.x = a->x / size;
	result.y = a->y / size;
	
	return result;
}
// ───────────────────────────────────────────────────────
 

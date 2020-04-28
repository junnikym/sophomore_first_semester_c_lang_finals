#include "types.h"

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

// ───────────────────────────────────────────────────────

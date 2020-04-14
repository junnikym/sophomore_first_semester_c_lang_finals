#include "types.h"

// ───────────────────────────────────────────────────────
// ───── COORD_2D functions ──────────────────────────────

// ─── setter functions

void zeroset_coord( COORD_2D x ) {
    x.x = 0;
    x.y = 0;
}

// ─── getter functions

double get_size( const COORD_2D* x ) {
    return sqrt( (x->x * x->x) + (x->y * x->y) );
}

// ─── arithmetic functions 

void coord_2d_add_ref(COORD_2D* target, const COORD_2D* rhs) {
    target->x += rhs->x;
    target->y += rhs->y;
}

void coord_2d_sub_ref(COORD_2D* target, const COORD_2D* rhs) {
    target->x -= rhs->x;
    target->y -= rhs->y;
}

void coord_2d_mul_ref(COORD_2D* target, const double* w) {
    target->x *= *w;
    target->y *= *w;
}

void coord_2d_div_ref(COORD_2D* target, const double* a) {
    target->x /= *a;
    target->y /= *a;
}

COORD_2D coord_2d_add(const COORD_2D* lhs, const COORD_2D* rhs) {
    COORD_2D result = { lhs->x + lhs->x, lhs->y + lhs->y };
    return result;
}

COORD_2D coord_2d_sub(const COORD_2D* lhs, const COORD_2D* rhs) {
    COORD_2D result = { lhs->x - lhs->x, lhs->y - lhs->y };
    return result;
}

COORD_2D coord_2d_mul(const COORD_2D* target, const double* w) {
    COORD_2D result = { target->x * *w, target->y * *w };
    return result;
}

COORD_2D coord_2d_div(const COORD_2D* target, const double* a) {
    COORD_2D result = { target->x / *a, target->y / *a };
    return result;
}


void normalize_ref(COORD_2D* vec, const double* vec_size) {
    vec->x /= *vec_size;
    vec->y /= *vec_size;
}

COORD_2D normalize(COORD_2D vec, const double* vec_size) {
    vec.x /= *vec_size;
    vec.y /= *vec_size;

    return vec;
}

// ───────────────────────────────────────────────────────

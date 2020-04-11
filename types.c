#include "types.h"

// ───────────────────────────────────────────────────────
// ───── COORD_2D functions ──────────────────────────────

void zeroset_coord( COORD_2D x ) {
    x.x = 0;
    x.y = 0;
}


double get_size( const COORD_2D* x ) {
    return sqrt( (x->x * x->x) + (x->y * x->y) );
}


void normalize_ref(COORD_2D *vec, const double* vec_size) {
    vec->x /= *vec_size;
    vec->y /= *vec_size;
}

COORD_2D normalize(COORD_2D vec, const double* vec_size) {
    vec.x /= *vec_size;
    vec.y /= *vec_size;

    return vec;
}

// ───────────────────────────────────────────────────────

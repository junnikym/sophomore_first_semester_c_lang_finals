#include "types.h"

// ───────────────────────────────────────────────────────
// ───── 2D_COORD functions ──────────────────────────────

void zeroset_coord( 2D_COORD x ) {
    x.x = 0;
    x.y = 0;
}


double get_size( const 2D_COORD* x ) {
    sqrt( (x->x * x->x) + (x->y * x->y) );
}


void normalize( 2D_COORD *vec , const int* vec_size ) {
    vec->x /= *vec_size;
    vec->y /= *vec_size;
}

void normalize( 2D_COORD *vec ) {
    normalize( vec, get_size(vec) );
}

2D_COORD normalize( 2D_COORD vec, const int* vec_size ) {
    vec.x /= *vec_size;
    vec.y /= *vec_size;

    return vec.x
}

2D_COORD normalize( const 2D_COORD *vec ) {
    normalize( *vec, get_size(vec) );
}

// ───────────────────────────────────────────────────────

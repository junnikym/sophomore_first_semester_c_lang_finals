#ifndef TYPES_H
#define TYPES_H

#include <math.h>

typedef struct _2D_COORD
    union {
        struct {
            double x, y;
        }
        double pos[2];
    }
} 2D_COORD;

void zeroset_coord( 2D_COORD x );

double get_size( _2D_COORD x );

void normalize( 2D_COORD *vec , const int* vec_size );
void normalize( 2D_COORD *vec );
2D_COORD normalize( 2D_COORD vec, const int* vec_size );
2D_COORD normalize( const 2D_COORD *vec );

#endif
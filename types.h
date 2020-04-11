#ifndef TYPES_H
#define TYPES_H

#include <math.h>

typedef struct _COORD_2D {
    union {
        struct {
            double x, y;
        };
        double pos[2];
    };
} COORD_2D;

void zeroset_coord( COORD_2D x );

double get_size(const COORD_2D* x);

COORD_2D normalize(COORD_2D vec, const double* vec_size);
void normalize_ref( COORD_2D *vec , const double* vec_size );

#endif
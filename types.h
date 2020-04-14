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

// ��������������������������������������������������������������������������������������������������������������
// ���������� COORD_2D functions ������������������������������������������������������������

// ������ setter functions

void zeroset_coord( COORD_2D x );

// ������ getter functions

double get_size(const COORD_2D* x);

// ������ arithmetic functions 

void coord_2d_add_ref(COORD_2D* target, const COORD_2D* rhs);
void coord_2d_sub_ref(COORD_2D* target, const COORD_2D* rhs);
void coord_2d_mul_ref(COORD_2D* target, const double* w);
void coord_2d_div_ref(COORD_2D* target, const double* a);

COORD_2D coord_2d_add(const COORD_2D* lhs, const COORD_2D* rhs);
COORD_2D coord_2d_sub(const COORD_2D* lhs, const COORD_2D* rhs);
COORD_2D coord_2d_mul(const COORD_2D* target, const double* w);
COORD_2D coord_2d_div(const COORD_2D* target, const double* a);


COORD_2D normalize(COORD_2D vec, const double* vec_size);
void normalize_ref(COORD_2D* vec, const double* vec_size);

// ��������������������������������������������������������������������������������������������������������������

#endif
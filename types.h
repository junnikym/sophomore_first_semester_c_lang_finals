#ifndef TYPES_H
#define TYPES_H

#include <math.h>

#define _TITLE_SIZE 32

typedef struct _VEC2 {
    union {
        struct {
            double x, y;
        };
        double pos[2];
    };
} VEC2;

// 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
// 式式式式式 VEC2 functions 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式

// 式式式 setter functions

void zeroset_coord( VEC2 x );

// 式式式 getter functions

double get_size(const VEC2* x);

// 式式式 arithmetic functions 

// assignment as arg
void vec2_add_assn(VEC2* target, const VEC2* rhs);
void vec2_sub_assn(VEC2* target, const VEC2* rhs);
void vec2_mul_assn(VEC2* target, double w);
void vec2_div_assn(VEC2* target, double a);


VEC2 vec2_add(const VEC2* lhs, const VEC2* rhs);
VEC2 vec2_sub(const VEC2* lhs, const VEC2* rhs);
VEC2 vec2_mul(const VEC2* target, const double* w);
VEC2 vec2_div(const VEC2* target, const double* a);


VEC2 normalize(VEC2 vec, const double* vec_size);
void normalize_assn(VEC2* vec, const double* vec_size);

// 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式

#endif
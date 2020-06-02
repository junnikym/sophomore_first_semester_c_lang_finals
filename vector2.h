#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>

// - D  : Direction
// - N  : Number (integer)
// - V2 : VEC2 (struct)
typedef enum __DIRECTION__ {        
    D_N_LEFT, D_N_RIGHT, D_N_UP, D_N_DOWN   
} _DIRCTION_;

typedef struct _VEC2 {
    union {
        struct {
            double x, y;
        };
        double pos[2];
    };
} VEC2;

// -------------------------------------------------------
// ----- VEC2 functions     ------------------------------

// ----- const static

static const VEC2 V2_ZERO       = {  0,  0 };
static const VEC2 D_V2_LEFT     = { -1,  0 };
static const VEC2 D_V2_RIGHT    = {  1,  0 };
static const VEC2 D_V2_UP       = {  0,  1 };
static const VEC2 D_V2_DOWN     = {  0, -1 };

// ----- setter functions

void zeroset_coord( VEC2 x );

// ----- getter functions

double get_size(const VEC2* x);

// ----- arithmetic functions 

// assignment as arg
void vec2_add_assn(VEC2* target, const VEC2* rhs);
void vec2_sub_assn(VEC2* target, const VEC2* rhs);
void vec2_mul_assn(VEC2* target, double w);
void vec2_div_assn(VEC2* target, double a);

VEC2 vec2_add(const VEC2* lhs, const VEC2* rhs);
VEC2 vec2_sub(const VEC2* lhs, const VEC2* rhs);
VEC2 vec2_mul(const VEC2* target, double w);
VEC2 vec2_div(const VEC2* target, double a);

void append_array_vec2(void* arr, int index, void* elem_addr);

VEC2 normalize(VEC2 vec, const double* vec_size);
void normalize_assn(VEC2* vec, const double* vec_size);

// -------------------------------------------------------

#endif /* VECTOR2_H */

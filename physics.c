#include "physics.h"

void init_force_arr(FORCE_ARRAY* arr) {
	arr->size = 1;
	arr->current = -1;
	arr->elems = (FORCE_ARRAY*)malloc(sizeof(FORCE_ARRAY) * arr->size);
}

void push_force_arr(FORCE_ARRAY* arr, VEC2 vec, int id) {
	arr->current++;

	if (arr->current > arr->size - 1) {
		arr->size += DYNAMIC_ARR_INC_UNIT;
		realloc(arr->elems, sizeof(FORCE_ARRAY) * arr->size);
	}

	arr->elems[arr->current].force_vec = vec;
	arr->elems[arr->current].identify = id;
	arr->elems[arr->current].delta_t = 0;
}

void pop_force_arr(FORCE_ARRAY* arr) {
	arr->current--;
}

void release_force_arr(FORCE_ARRAY* arr) {
	free(arr);
}

void accelerate(VEC2 position, VEC2 accel) {
    
}

void friction(VEC2* force, const double* constant) {
    vec2_mul_assn(force, *constant);
}
#ifndef UTILITY_H
#define UTILITY_H

#include <stdlib.h>
#include <math.h>

// 만약 4에서 7까지 반복해야 하는 일이 생길 경우
// 그 사이 값에서만 루프를 돌 수 있도록 도와주는 함수
int range_loop ( unsigned int min, unsigned int max, int* current );

#endif
 

#ifndef RANDOM_GEN_H
#define RANDOM_GEN_H
 
#include <stdlib.h>
#include <time.h> 

#include "vector2.h"
#include "memory.h"

#include "GLFW/glfw3.h"

#define __MAX_GENERATEING 10

// 범위내에서 랜덤으로 위치를 선정해 주는 함수
VEC2 random_place(VEC2 center, double range);

void generate_asteroid( VEC2 where );
void generate_rand_asteroid( VEC2 center, double range );

void planet_generator();

#endif
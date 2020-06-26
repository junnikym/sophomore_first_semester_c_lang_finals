#ifndef RANDOM_GEN_H
#define RANDOM_GEN_H
 
#include <stdlib.h>
#include <time.h> 

#include "vector2.h"
#include "memory.h"

#include "GLFW/glfw3.h"

#define __MAX_GENERATEING 10

// ���������� �������� ��ġ�� ������ �ִ� �Լ�
VEC2 random_place(VEC2 center, double range);

void generate_asteroid( VEC2 where );
void generate_rand_asteroid( VEC2 center, double range );

void planet_generator();

#endif
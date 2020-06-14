#ifndef TYPES_H
#define TYPES_H

#include <math.h>
// 제곱을 구하는 메크로 함수
#define SQUARE(x) ((x)*(x))
// x의 3승을 구하는 메크로 함수
#define CUBIC(x) ((x)*(x)*(x))

// 제목 사이즈를 지정해줄 메크로 상수
#define _TITLE_SIZE 32

// 중력 상수
const static double __EARTH_GRAVITY_CONSTANT = 4.0;

// 마찰 상수
const static double __BASIC_FIRCTION_CONSTANT = 0.94;

// OBJECT 구조체에 요소를 추가할때 어떤 요소를 추가할지 구분하기
// 위해 만든 열거형
typedef enum __OBJECT_ELEMENT__ {
	__FORCE__,
	__ENTITY__,
	__OBJECT__
} _OBJCT_ELEMENT_;

typedef _OBJCT_ELEMENT_ _OBJ_ELEM_;

#endif /* TYPES_H */
















       

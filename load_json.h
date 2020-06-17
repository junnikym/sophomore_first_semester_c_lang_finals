#ifndef LOAD_JSON_H
#define LOAD_JSON_H

#include <stdio.h>     // 파일 처리 함수가 선언된 헤더 파일
#include <stdlib.h>    // malloc, free, atof 함수가 선언된 헤더 파일
#include <stdbool.h>   // bool, true, false가 정의된 헤더 파일
#include <string.h>    // strchr, strcmp, memset, memcpy 함수가 선언된 헤더 파일

#include "opengl/texture.h"

#include "tree.h"
#include "vector2.h"

// 토큰 종류 열거형
typedef enum _TOKEN_TYPE {
    TOKEN_STRING,    // 문자열 토큰
    TOKEN_NUMBER,    // 숫자 토큰
} TOKEN_TYPE;

// 토큰 구조체
typedef struct _TOKEN {
    TOKEN_TYPE type;   	  // 토큰 종류
    union {            	  // 두 종류 중 한 종류만 저장할 것이므로 공용체로 만듦
        char *string;     // 문자열 포인터
        double number;    // 실수형 숫자
    };
    bool isArray;         // 현재 토큰이 배열인지 표시
} TOKEN;

#define TOKEN_COUNT 20    // 토큰의 최대 개수

// JSON 구조체
typedef struct _JSON {
    TOKEN tokens[TOKEN_COUNT]; // 토큰 배열
} JSON;

char *json_readFile(char *filename, int *readSize);
void json_parseJSON(char *doc, int size, JSON *json);
void json_freeJSON(JSON *json);
char *json_getString(JSON *json, char *key);
char *json_getArrayString(JSON *json, char *key, int index);
int json_getArrayCount(JSON *json, char *key);
double json_getNumber(JSON *json, char *key);

int load_texture_package(char* path, TREE* memory);

#endif

#include "load_json.h"

char *json_readFile(char *filename, int *readSize)    // 파일을 읽어서 내용을 반환하는 함수
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
        return NULL;

    int size;
    char *buffer;

    // 파일 크기 구하기
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // 파일 크기 + NULL 공간만큼 메모리를 할당하고 0으로 초기화
    buffer = malloc(size + 1);
    memset(buffer, 0, size + 1);

    // 파일 내용 읽기
    if (fread(buffer, size, 1, fp) < 1)
    {
        *readSize = 0;
        free(buffer);
        fclose(fp);
        return NULL;
    }

    // 파일 크기를 넘겨줌
    *readSize = size;

    fclose(fp);    // 파일 포인터 닫기

    return buffer;
}

void json_parseJSON(char *doc, int size, JSON *json)    // JSON 파싱 함수
{
    int tokenIndex = 0;    // 토큰 인덱스
    int pos = 0;           // 문자 검색 위치를 저장하는 변수
    int arr_continue = 0;

    if (doc[pos] != '{')   // 문서의 시작이 {인지 검사
        return;

    pos++;    // 다음 문자로

    while (pos < size)       // 문서 크기만큼 반복
    {
        switch (doc[pos])    // 문자의 종류에 따라 분기
        {
        case '"':            // 문자가 "이면 문자열
        {
            // 문자열의 시작 위치를 구함. 맨 앞의 "를 제외하기 위해 + 1
            char *begin = doc + pos + 1;

            // 문자열의 끝 위치를 구함. 다음 "의 위치
            char *end = strchr(begin, '"');
            if (end == NULL) // "가 없으면 잘못된 문법이므로 
                break;       // 반복을 종료

            int stringLength = end - begin;    // 문자열의 실제 길이는 끝 위치 - 시작 위치

            // 토큰 배열에 문자열 저장
            // 토큰 종류는 문자열
            json->tokens[tokenIndex].type = TOKEN_STRING;
            // 문자열 길이 + NULL 공간만큼 메모리 할당
            json->tokens[tokenIndex].string = malloc(stringLength + 1);
            // 할당한 메모리를 0으로 초기화
            memset(json->tokens[tokenIndex].string, 0, stringLength + 1);

            // 문서에서 문자열을 토큰에 저장
            // 문자열 시작 위치에서 문자열 길이만큼만 복사
            memcpy(json->tokens[tokenIndex].string, begin, stringLength);

            tokenIndex++;    // 토큰 인덱스 증가

            pos = pos + stringLength + 1;    // 현재 위치 + 문자열 길이 + "(+ 1)
        }
        break;
        case '[':            // 문자가 [이면 배열
        {
            pos++;           // 다음 문자로
            arr_continue++;

            while (arr_continue != 0)    // 닫는 ]가 나오면 반복 종료
            {
                if ( doc[pos] == '[' ) {
                    arr_continue++;
                }

                else if ( doc[pos] == ']' ) {
                    arr_continue--;
                }

                // 여기서는 문자열만 처리
                else if (doc[pos] == '"')   // 문자가 "이면 문자열
                {
                    // 문자열의 시작 위치를 구함. 맨 앞의 "를 제외하기 위해 + 1
                    char *begin = doc + pos + 1;

                    // 문자열의 끝 위치를 구함. 다음 "의 위치
                    char *end = strchr(begin, '"');
                    if (end == NULL)   // "가 없으면 잘못된 문법이므로
                        break;         // 반복을 종료

                    int stringLength = end - begin;    // 문자열의 실제 길이는 끝 위치 - 시작 위치

                    // 토큰 배열에 문자열 저장
                    // 토큰 종류는 문자열
                    json->tokens[tokenIndex].type = TOKEN_STRING;
                    // 문자열 길이 + NULL 공간만큼 메모리 할당
                    json->tokens[tokenIndex].string = malloc(stringLength + 1);
                    // 현재 문자열은 배열의 요소
                    json->tokens[tokenIndex].isArray = arr_continue;
                    // 할당한 메모리를 0으로 초기화
                    memset(json->tokens[tokenIndex].string, 0, stringLength + 1);

                    // 문서에서 문자열을 토큰에 저장
                    // 문자열 시작 위치에서 문자열 길이만큼만 복사
                    memcpy(json->tokens[tokenIndex].string, begin, stringLength);

                    tokenIndex++;    // 토큰 인덱스 증가

                    pos = pos + stringLength + 1;    // 현재 위치 + 문자열 길이 + "(+ 1)
                }

                pos++;    // 다음 문자로
            }
        }
        break;
        case '0': case '1': case '2': case '3': case '4': case '5':    // 문자가 숫자이면
        case '6': case '7': case '8': case '9': case '-':              // -는 음수일 때
        {
            // 문자열의 시작 위치를 구함
            char *begin = doc + pos;
            char *end;
            char *buffer;

            // 문자열의 끝 위치를 구함. ,가 나오거나
            end = strchr(doc + pos, ',');
            if (end == NULL)
            {
                // }가 나오면 문자열이 끝남
                end = strchr(doc + pos, '}');
                if (end == NULL)    // }가 없으면 잘못된 문법이므로
                    break;          // 반복을 종료
            }

            int stringLength = end - begin;    // 문자열의 실제 길이는 끝 위치 - 시작 위치

            // 문자열 길이 + NULL 공간만큼 메모리 할당
            buffer = malloc(stringLength + 1);
            // 할당한 메모리를 0으로 초기화
            memset(buffer, 0, stringLength + 1);

            // 문서에서 문자열을 버퍼에 저장
            // 문자열 시작 위치에서 문자열 길이만큼만 복사
            memcpy(buffer, begin, stringLength);

            // 토큰 종류는 숫자
            json->tokens[tokenIndex].type = TOKEN_NUMBER;  
            // 문자열을 숫자로 변환하여 토큰에 저장
            json->tokens[tokenIndex].number = atof(buffer);

            free(buffer);    // 버퍼 해제

            tokenIndex++;    // 토큰 인덱스 증가

            pos = pos + stringLength + 1;    // 현재 위치 + 문자열 길이 + , 또는 }(+ 1)
        }
        break;
        }

        pos++; // 다음 문자로
    }
}

void json_freeJSON(JSON *json)    // JSON 해제 함수
{
    for (int i = 0; i < TOKEN_COUNT; i++)            // 토큰 개수만큼 반복
    {
        if (json->tokens[i].type == TOKEN_STRING)    // 토큰 종류가 문자열이면
            free(json->tokens[i].string);            // 동적 메모리 해제
    }
}

char *json_getString(JSON *json, char *key)    // 키에 해당하는 문자열을 가져오는 함수
{
    for (int i = 0; i < TOKEN_COUNT; i++)    // 토큰 개수만큼 반복
    {
        // 토큰 종류가 문자열이면서 토큰의 문자열이 키와 일치하면
        if (json->tokens[i].type == TOKEN_STRING && 
            strcmp(json->tokens[i].string, key) == 0)
        {
            // 바로 뒤의 토큰(i + 1)이 문자열이면
            if (json->tokens[i + 1].type == TOKEN_STRING)
                return json->tokens[i + 1].string;    // 바로 뒤에 있는 토큰의 문자열 반환
        }
    }

    return NULL;    // 키를 찾지 못했으면 NULL을 반환
}

// 키에 해당하는 배열 중 인덱스를 지정하여 문자열을 가져오는 함수
char *json_getArrayString(JSON *json, char *key, int index)
{
    for (int i = 0; i < TOKEN_COUNT; i++)    // 토큰 개수만큼 반복
    {
        // 토큰 종류가 문자열이면서 토큰의 문자열이 키와 일치한다면
        if (json->tokens[i].type == TOKEN_STRING &&
            strcmp(json->tokens[i].string, key) == 0)
        {
            // 바로 뒤의 토큰(i + 1)부터 배열의 요소
            // 인덱스를 지정한 토큰이 문자열이면서 배열이면
            if (json->tokens[i + 1 + index].type == TOKEN_STRING && 
                json->tokens[i + 1 + index].isArray != 0)
                return json->tokens[i + 1 + index].string;    // 해당 토큰의 문자열 반환
        }
    }

    return NULL;    // 키를 찾지 못했으면 NULL을 반환
}

int json_getArrayCount(JSON *json, char *key)     // 키에 해당하는 배열의 요소 개수를 구하는 함수
{
    for (int i = 0; i < TOKEN_COUNT; i++)    // 토큰 개수만큼 반복
    {
        // 토큰 종류가 문자열이면서 토큰의 문자열이 키와 일치한다면
        if (json->tokens[i].type == TOKEN_STRING &&
            strcmp(json->tokens[i].string, key) == 0)
        {
            // 바로 뒤의 토큰(i + 1)부터 isArray가 true인 토큰의 개수를 세어서 반환
            int j = 0;
            while (json->tokens[i + 1 + j].isArray != 0)
                j++;

            return j;
        }
    }

    return 0;    // 키를 찾지 못했으면 0을 반환
}

double json_getNumber(JSON *json, char *key)    // 키에 해당하는 숫자를 가져오는 함수
{
    for (int i = 0; i < TOKEN_COUNT; i++)    // 토큰 개수만큼 반복
    {
        // 토큰 종류가 숫자이면서 토큰의 문자열이 키와 일치한다면
        if (json->tokens[i].type == TOKEN_STRING &&
            strcmp(json->tokens[i].string, key) == 0)
        {
            // 바로 뒤의 토큰(i + 1)이 숫자이면
            if (json->tokens[i + 1].type == TOKEN_NUMBER)
                return json->tokens[i + 1].number;    // 바로 뒤에 있는 토큰의 숫자 반환
        }
    }

    return 0.0;    // 키를 찾지 못했으면 0.0을 반환
}

int load_texture_package(char* path, TREE* memory) {

	// - VARIABLE FOR JSON

    int inner_i = 0, outer_i = 0;
	int size = 0, inner_size = 0;
	int arr_size = 0;
	char* bring_str = "";
	
    // - VARIABLE FOR TEXTURE

	char* title = "";
	char* ext = "";
	char texture_path[256] = "";
	VEC2 texture_begin = (VEC2){1, 1};
	VEC2 texture_size = (VEC2){1, 1};
	
	GLuint texture = 0;

    GLfloat buf_vertice[32] = { 0 };

    memcpy ( buf_vertice, g_SQUARE_VERTICES, sizeof ( buf_vertice ) );

    BUFFER_ATTRIBUTES buf_obj_attr = {
        buf_vertice,
        sizeof ( buf_vertice ),
        g_SQUARE_INDICES,
        sizeof ( g_SQUARE_INDICES )
    };
	
	char *doc = json_readFile (path, &size);
	if(doc == NULL)
		return -1;

	JSON json = { 0, };

	json_parseJSON(doc, size, &json);

	printf("loading textures :\n");
	arr_size = json_getArrayCount(&json, "textures");
	for(outer_i = 0; outer_i < arr_size; outer_i++) {

        title = json_getArrayString(&json, "textures", outer_i);
		inner_size = json_getArrayCount(&json, title );
        
		for (inner_i = 0; inner_i < inner_size; inner_i+=2) {
            outer_i +=2;
			
			bring_str = json_getArrayString(&json, title, inner_i);

			if ( strcmp(bring_str, "extension") == 0 ) {
				ext = json_getArrayString(&json, title, inner_i+1);
			}
			
			else if ( strcmp(bring_str, "path") == 0 ) {
                texture_path[0] = '\0';

                sprintf ( texture_path, "%s%s", 
                          TEXTURE_FOLDER_PATH, 
                          json_getArrayString ( &json, title, inner_i + 1 ) );
			}
			
			else if ( strcmp(bring_str, "size_x") == 0 ) {
				bring_str = json_getArrayString(&json, title, inner_i+1);
				texture_size.x = atof(bring_str);
			}
			else if ( strcmp(bring_str, "size_y") == 0 ) {
				bring_str = json_getArrayString(&json, title, inner_i+1);
				texture_size.y = atof(bring_str);
			}
			
			else if ( strcmp(bring_str, "texture_begin_x") == 0 ) {
				bring_str = json_getArrayString(&json, title, inner_i+1);
				texture_begin.x = atof(bring_str);
			}
			else if ( strcmp(bring_str, "texture_begin_y") == 0 ) {
				bring_str = json_getArrayString(&json, title, inner_i+1);
				texture_begin.y = atof(bring_str);
			}

            else if ( strcmp ( bring_str, "end" ) == 0 ) {
                //outer_i += 1;
                inner_size = inner_i;
            }
			
		}
		
        // ! TODO : set z-buffer
        set_square_vertices ( buf_vertice, texture_size, 1.0f, texture_begin );

        if ( strcmp(ext, "dds") == 0 ) {
            texture = gl_load_DDS ( texture_path );
        }
        else if ( strcmp ( ext, "bmp" ) == 0 ) {
            printf("called by BMP : %s \n", title);
            texture = gl_load_BMP ( texture_path );
        }

        if ( texture == 0 )
            return -1;

        g_buf_obj_insert ( title,
                           texture,
                           &buf_obj_attr );

	}

	json_freeJSON(&json);

	free(doc);
	
	return 0;
}

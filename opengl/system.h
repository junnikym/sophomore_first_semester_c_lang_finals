#ifndef GL_SYSTEM_H		// 해더파일이 여러 파일에서 중복으로
#define GL_SYSTEM_H		// 로드되는 것을 방지

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include  <GLFW/glfw3.h>	

#include "callback.h"
#include "graphics.h"
#include "camera.h"

#include "../memory.h"
#include "../object.h"
#include "../utility.h"

typedef struct _WINDOW {
    GLFWwindow* window;
    int width, height;
    const char* title;
} WINDOW;

/*  gl_system_init : 
 * 화면을 띄우기위해 필요한 요소들을 초기화하는 함수
 */
int     gl_system_init		( WINDOW* p_out,	
							  int width,
							  int height,
							  const char* title );

/*  gl_system_run : 
 * 화면을 진행하기 위해 무한 루프를 통해 프로그램을 진행,
 * 게임에 필요한 것을 실행해주는 함수.
 */
void    gl_system_run 		( WINDOW* window );

/*  gl_system_shutdown : 
 * 화면을 종료하기 위해 사용한 OpenGL 요소들을 해제해주는 함수
 */
void    gl_system_shutdown 	( WINDOW* window );

#endif  /* GL_SYSTEM_H */


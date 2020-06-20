#ifndef OPEN_GL_GRAPHICS_H
#define OPEN_GL_GRAPHICS_H

#include "../memory.h"

#include "buffer_obj.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32				// 윈도우 기반의 컴퓨터일 경우
	#include <malloc.h>		// malloc.h를 포함해 줌
#endif

// ------------------------------------------------------- //
// ----- OpenGL Graphics functions		------------------

void	gl_clear_screen		( );	// 화면을 모두 지워주는 함수

void	gl_draw_sprite_obj 	( const BUFFER_OBJECT* obj,		// 객체를 그려주는 함수
							  mat4 MVP,
							  const VEC2* current_sprite_pos,
							  const vec4* bland_color );
void	gl_rander			 	( );	// system의 run과 같은 역할

// ------------------------------------------------------- //

#endif
#ifndef OPEN_GL_GRAPHICS_H
#define OPEN_GL_GRAPHICS_H

#include "../memory.h"

#include "buffer_obj.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
	#include <malloc.h>
#endif

// ------------------------------------------------------- //
// ----- OpenGL Graphics functions		------------------

void	gl_clear_screen		 ();

void 	gl_draw_obj 		 ( const BUFFER_OBJECT* shader, mat4 MVP );
void	gl_draw_sprite_obj ( const BUFFER_OBJECT* shader,
							mat4 MVP,
							const VEC2* current_sprite_pos );
void	gl_rander			 ( /* OBJ Array */ );

void	gl_shutdown_graphics( BUFFER_OBJECT* x );

// ------------------------------------------------------- //

#endif

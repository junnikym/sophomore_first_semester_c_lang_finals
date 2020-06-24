#include "vector2.h"
#include "entity.h"
#include "memory.h"

#define __FONT_SIZE 1.0

GLuint g_shader_id;

static ENTITY g_TEXT;

void Text_drew(char* text, int pos_x, int pos_y, double font_size, double letter_spacing);
void text_load();
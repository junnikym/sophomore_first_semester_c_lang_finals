#ifndef IMG_SPRITE_H
#define IMG_SPRITE_H

#include "../vector2.h"

typedef struct {
	char* img_path;
	
	VEC2 row_n_column_size;
	VEC2 start_frame;
	
	int frame_speed;
} IMG_SPRITE;

#endif

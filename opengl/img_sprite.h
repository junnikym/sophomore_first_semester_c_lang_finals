#ifndef IMG_SPRITE_H
#define IMG_SPRITE_H

#include "../types.h"

typedef struct {
	char* img_path;		
	VEC2 row_n_column_size;
	VEC2 start_frame;
	int frame_frame;
} IMG_SPRITE;

#endif

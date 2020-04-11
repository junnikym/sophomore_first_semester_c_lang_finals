#ifndef ENTITY_H
#define ENTITY_H

#include "types.h"

typedef struct _ENTITY {
    COORD_2D position;
    COORD_2D direction_vec;
    COORD_2D force_vec;
} ENTITY;

#endif
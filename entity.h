#ifndef ENTITY_H
#define ENTITY_H

typedef struct _ENTITY {
    2D_COORD position;
    2D_COORD direction_vec;
    2D_COORD force_vec;
} ENTITY;

#endif
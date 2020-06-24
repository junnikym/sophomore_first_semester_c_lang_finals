#ifndef INVENTORY_H
#define INVENTORY_H

#include "../opengl/buffer_obj.h"
#include "../object.h"

#include "../memory.h"

static OBJECT g_INVENTORY;
static int open_inventory = 0;
static int items_in_inventory[9] = { 0 };

void toggle_inventory();
int is_open_inventory();

void init_inventory();
void show_inventory(const VEC2* cam_pos);

#endif // !INVENTORY_H

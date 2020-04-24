#ifndef MEMORY_H
#define MEMORY_H

#include "object.h"

static DYNAMIC_ARRAY g_objects;
static OBJECT* g_user_obj;

void setting_for_test();

void init_memory();

void push_g_obj(void* elem);

void release_memory();

#endif
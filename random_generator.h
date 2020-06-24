#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#include <stdlib.h>
#include <time.h>

#include "object.h"

void range_based_gen ( VEC2 pos, double range, void* out, void (*generator)(void* out) );

void planet_generator (void* out);

#endif
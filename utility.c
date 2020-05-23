#include "utility.h"

int loop_section ( int min, int max, int* current ) {
	if ( current < min ) 
		current = max;
	
	else if ( current > max ) 
		current = min;

	return current;
}
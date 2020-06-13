#include "utility.h"

#include <stdio.h>

int range_loop ( unsigned int min, unsigned int max, int* current ) {
	if ( *current > (int)max ) {
		*current = min + ( *current - 1 - max );
		
		range_loop(min, max, current);
	}
	else if ( *current < (int)min ) {
		*current = max - ( (*current < 0) ? (abs(*current) + min - 1) : (min - *current - 1) );
	
		range_loop(min, max, current);
	}
	
	return *current;
}
 

#include "physics.h"

void accelerate(COORD_2D position, COORD_2D accel) {
    
}

void set_friction_const( double c );
void friction();

void set_gravity_const( double c ) {
    PHY_GRAVITY_CONST = c;
}

void set_friction_const( double c ) {
    PHY_FRICTION_CONST = c;
}
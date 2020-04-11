#include "physics.h"

/*
void accelerate();

void set_gravity_const( double c );
void gravity();

void set_friction_const( double c );
void friction();
*/

void set_gravity_const( double c ) {
    PHY_GRAVITY_CONST = c;
}

void set_friction_const( double c ) {
    PHY_FRICTION_CONST = c;
}
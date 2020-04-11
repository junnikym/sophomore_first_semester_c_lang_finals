#ifndef PHYSICS_H
#define PHYSICS_H

int PHY_GRAVITY_CONST = 0;
int PHY_FRICTION_CONST = 0;

void accelerate();

void set_gravity_const( double c );
void gravity();

void set_friction_const( double c );
void friction();

#endif
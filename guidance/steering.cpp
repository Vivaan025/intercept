#include "steering.h"

void applySteering(
    Missile& missile,
    float angularAccel)
{
    float maxAngularAccel = 0.01f;

    if(angularAccel > maxAngularAccel)
        angularAccel = maxAngularAccel;

    if(angularAccel < -maxAngularAccel)
        angularAccel = -maxAngularAccel;

    missile.angularVel += angularAccel;

    // Drag
    float angularDrag = 0.98f;
    missile.angularVel *= angularDrag;

    // Clamp angular velocity
    float maxAngularVel = 0.08f;

    if(missile.angularVel > maxAngularVel)
        missile.angularVel = maxAngularVel;

    if(missile.angularVel < -maxAngularVel)
        missile.angularVel = -maxAngularVel;

    missile.angle += missile.angularVel;
}
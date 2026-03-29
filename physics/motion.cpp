#include "motion.h"
#include <cmath>
#include "../entities/missile.h"

void applyPhysics(Missile& missile) {
    
    float dirX = cos(missile.angle);
    float dirY = sin(missile.angle);

    float thrust = 0.0005f;
    missile.accX = dirX * thrust;
    missile.accY = dirY * thrust;

    missile.velX += missile.accX;
    missile.velY += missile.accY;

    float drag = 0.99f;
    missile.velX *= drag;
    missile.velY *= drag;

    missile.x += missile.velX;
    missile.y += missile.velY;

}
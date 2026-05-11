#include "los.h"
#include <cmath>

float calculateLOSRate(Drone& drone, Missile& missile)
{
    float dx = drone.x - missile.x;
    float dy = drone.y - missile.y;

    float relativeVelX = drone.velX - missile.velX;
    float relativeVelY = drone.velY - missile.velY;

    float distanceSquared = dx * dx + dy * dy;

    if(distanceSquared < 0.0001f)
        return 0.0f;

    // LOS angular rate
    float losRate =
        (dx * relativeVelY - dy * relativeVelX)
        / distanceSquared;

    return losRate;
}
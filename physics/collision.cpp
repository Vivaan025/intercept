#include "collision.h"
#include <cmath>

bool checkCollision(Drone& drone, Missile& missile)
{
    float dx = drone.x - missile.x;
    float dy = drone.y - missile.y;

    float distance = sqrt(dx * dx + dy * dy);
    float collisionRadius = drone.radius + missile.radius;

    return distance < collisionRadius;
}
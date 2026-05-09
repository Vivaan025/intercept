#include "lead.h"
#include <cmath>

void computeLead(
    Drone& drone,
    Missile& missile,
    float& futureX,
    float& futureY
) {

    float velX = drone.x - drone.prevX;
    float velY = drone.y - drone.prevY;

    float dx = drone.x - missile.x;
    float dy = drone.y - missile.y;

    float distance = sqrt(dx * dx + dy * dy);

    float missileSpeed =
        sqrt(missile.velX * missile.velX +
             missile.velY * missile.velY);

    float t = distance / (missileSpeed * 10.0f);

    if(t > 5.0f)
        t = 5.0f;

    futureX = drone.x + velX * t;
    futureY = drone.y + velY * t;
}
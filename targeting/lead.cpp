#include "lead.h"
#include <cmath>

LeadData computeLeadPosition(
    Drone& drone,
    Missile& missile
) {
    LeadData leadData;

    float velX = drone.x - drone.prevX;
    float velY = drone.y - drone.prevY;

    float dx0 = drone.x - missile.x;
    float dy0 = drone.y - missile.y;

    float distance = sqrt(dx0 * dx0 + dy0 * dy0);

    float missileSpeed =
        sqrt(missile.velX * missile.velX +
             missile.velY * missile.velY);

    float t = distance / (missileSpeed * 10.0f);

    if(t > 5.0f)
        t = 5.0f;

    leadData.futureX = drone.x + velX * t;
    leadData.futureY = drone.y + velY * t;

    float dy = leadData.futureY - missile.y;
    float dx = leadData.futureX - missile.x;
    
    leadData.targetAngle = atan2(dy, dx);

    return leadData;
}
#pragma once

#include "../entities/drone.h"
#include "../entities/missile.h"

struct LeadData
{
    float futureX;
    float futureY;
    float targetAngle;
};

LeadData computeLeadPosition(
    Drone& drone,
    Missile& missile
);
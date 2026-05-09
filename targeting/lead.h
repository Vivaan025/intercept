#pragma once

#include "../entities/drone.h"
#include "../entities/missile.h"

void computeLeadPosition(
    Drone& drone,
    Missile& missile,

    float& futureX,
    float& futureY
);
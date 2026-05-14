#pragma once

#include <vector>

#include "trail_point.h"

struct Drone
{
    float x, y;
    float prevX, prevY;
    float velX, velY;
    // collision radius (meters, world units)
    float radius = 0.02f;

    bool active = true;

    std::vector<TrailPoint> trail;

    void update(float time);
};
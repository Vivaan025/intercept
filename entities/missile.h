#pragma once

#include <vector>

#include "trail_point.h"

struct Missile
{
    float x, y;

    // velocity components
    float velX, velY;

    // acceleration components
    float accX, accY;

    float angle;
    float speed;

    // angular velocity for realism, just like we did it for position and velocity,
    // we can have an angular velocity that changes the angle over time, simulating the missile's ability to turn.
    // This would make the interception more realistic, as missiles typically have a limited turning rate.
    float angularVel;

    float prevError;
    float integralError;
    // collision radius (meters, world units)
    float radius = 0.01f;

    // destroy missile
    bool active = true;

    std::vector<TrailPoint> trail;
};
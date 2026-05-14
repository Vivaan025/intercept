#pragma once

struct Drone
{
    float x, y;
    float prevX, prevY;
    float velX, velY;
    // collision radius (meters, world units)
    float radius = 0.02f;

    bool active = true;

    void update(float time);
};
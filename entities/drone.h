#pragma once

struct Drone {
    float x, y;
    float prevX, prevY;
    float velX, velY;
    bool active = true;

    void update(float time);
};
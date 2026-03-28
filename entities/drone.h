#pragma once

struct Drone {
    float x, y;
    float prevX, prevY;
    bool active = true;

    void update(float time);
};
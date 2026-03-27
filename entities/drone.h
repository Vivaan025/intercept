#pragma once

struct Drone {
    float x, y;
    float prevX, prevY;

    void update(float time);
};
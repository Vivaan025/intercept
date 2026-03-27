#include "drone.h"
#include <cmath>

void Drone::update(float time) {
    prevX = x;
    prevY = y;

    x = 0.5f * cos(time);
    y = 0.5f * sin(time);
}
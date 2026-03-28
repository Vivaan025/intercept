#pragma once

struct Missile {
    float x, y;

    //velocity components
    float velX, velY;

    //acceleration components
    float accX, accY;

    float angle;
    float speed;

    bool active = true;
};
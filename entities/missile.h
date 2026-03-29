#pragma once

struct Missile {
    float x, y;

    //velocity components
    float velX, velY;

    //acceleration components
    float accX, accY;

    float angle;
    float speed;

    //angular velocity for realism, just like we did it for position and velocity,
    //we can have an angular velocity that changes the angle over time, simulating the missile's ability to turn.
    //This would make the interception more realistic, as missiles typically have a limited turning rate.
    float angularVel;


    //destroy missile
    bool active = true;
};
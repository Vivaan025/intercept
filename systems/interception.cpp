#include "interception.h"
#include "../math/angle.h"
#include <cmath>

static float prevAngle = 0.0f;

void updateInterception(Drone& drone, Missile& missile) {

    // float velX = drone.x - drone.prevX;
    // float velY = drone.y - drone.prevY;
    float dy = drone.y - missile.y;
    float dx = drone.x - missile.x;
    float currentAngle = missile.angle;

    float targetAngle = atan2(dy, dx);

    float angleDiff = angleDifference(targetAngle, missile.angle);

    // float t = 20.0f;

    // float futureX = drone.x + velX * t;
    // float futureY = drone.y + velY * t;

    // float dirX = futureX - missile.x;
    // float dirY = futureY - missile.y;

    float gain = 3.0f;

    float turn = gain * angleDiff;

    float maxTurn = 0.03f;

    if(turn > maxTurn) turn = maxTurn;
    if(turn < -maxTurn) turn = -maxTurn;

    missile.angle += turn;

    missile.velX = cos(missile.angle) * missile.speed;
    missile.velY = sin(missile.angle) * missile.speed;

    // float length = sqrt(dirX * dirX + dirY * dirY);

    // if (length > 0.0001f) {
    //     dirX /= length;
    //     dirY /= length;
    // }

    missile.x += missile.velX;
    missile.y += missile.velY;
}
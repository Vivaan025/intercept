#include "interception.h"
#include "../math/angle.h"
#include <cmath>
#include <iostream>
#include "../physics/motion.h"

void updateInterception(Drone& drone, Missile& missile) {

    // float velX = drone.x - drone.prevX;
    // float velY = drone.y - drone.prevY;

    //TARGET ANGLE ------------------------------------------------------
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

    //TURNING ------------------------------------------------------
    // float gain = 3.0f;

    // float turn = gain * angleDiff;

    // float maxTurn = 0.03f;

    // if(turn > maxTurn) turn = maxTurn;
    // if(turn < -maxTurn) turn = -maxTurn;

    //PID -------------------------------------------------------------
    float kp = 3.0f; // Proportional gain
    float kd = 2.0f; // Derivative gain
    float ki = 0.001f; // Integral gain

    float error = angleDifference(targetAngle, missile.angle);

    //Derivative term
    float derivative = error - missile.prevError;

    //Integral term
    missile.integralError += error;

    float maxIntegral = 5.0f;

    if (missile.integralError > maxIntegral)
        missile.integralError = maxIntegral;

    if (missile.integralError < -maxIntegral)
        missile.integralError = -maxIntegral;

    //PID output
    float angularAccel = kp * error + kd * derivative + ki * missile.integralError;
    std::cout << "Error: " << error
              << " Derivative: " << derivative
              << " Integral: " << missile.integralError
              << " Angular Accel: " << angularAccel << std::endl;

    // Update previous error for next iteration
    missile.prevError = error;

    // missile.angle += turn;

    //angular accleration
    // float angularAccel = gain * angleDiff; 

    float maxAngularAccel = 0.002f;
    if(angularAccel > maxAngularAccel) angularAccel = maxAngularAccel;
    if(angularAccel < -maxAngularAccel) angularAccel = -maxAngularAccel;

    missile.angularVel += angularAccel;

    float angularDrag = 0.98f;
    missile.angularVel *= angularDrag;

    float maxAngularVel = 0.05f;
    if(missile.angularVel > maxAngularVel) missile.angularVel = maxAngularVel;
    if(missile.angularVel < -maxAngularVel) missile.angularVel = -maxAngularVel;

    missile.angle += missile.angularVel;

    



    //PHYSICS ------------------------------------------------------
    applyPhysics(missile);

    //MOVEMENT ------------------------------------------------------

    //NOW HANDLES IN PHYSICS > motion.cpp
    // missile.velX = cos(missile.angle) * missile.speed;
    // missile.velY = sin(missile.angle) * missile.speed;

    // float length = sqrt(dirX * dirX + dirY * dirY);

    // if (length > 0.0001f) {
    //     dirX /= length;
    //     dirY /= length;
    // }

    // missile.x += missile.velX;
    // missile.y += missile.velY;

}
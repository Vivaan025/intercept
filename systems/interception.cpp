#include "interception.h"
#include <cmath>

#include "../targeting/lead.h"
#include "../targeting/los.h"

#include "../guidance/pid.h"
#include "../guidance/steering.h"
#include "../guidance/proportional_navigation.h"

#include "../math/angle.h"
#include "../physics/motion.h"
#include "../physics/collision.h"

#include <iostream>

void updateInterception(Drone &drone, Missile &missile)
{
    if (!missile.active)
        return;

    //============================
    // Target Prediction
    //============================

    LeadData leadData;
    leadData = computeLeadPosition(drone, missile);

    //============================
    // Guidance System
    //============================

    float error = angleDifference(leadData.targetAngle, missile.angle);

    static PID pid = {3.0f, 0.0f, 2.0f, 0.0f, 0.0f};

    float pidOutput = updatePID(pid, error);

    //============================
    // Apply Steering
    //============================

    applySteering(missile, pidOutput);

    //============================
    // Physics Update
    //============================
    applyPhysics(missile);

    //============================
    // Collision Check
    //============================
    if (checkCollision(drone, missile))
    {
        missile.active = false;
        drone.active = false;
        std::cout << "Collision Detected!" << std::endl;
    }

    std::cout << "Error: " << error
              << " PID Output: " << pidOutput
              << " Missile Angle: " << missile.angle
              << " Target Angle: " << leadData.targetAngle
              << std::endl;
}

// void updateInterception(Drone &drone, Missile &missile)
// {

//     // VELOCITY (change in position)
//     float velX = drone.x - drone.prevX;
//     float velY = drone.y - drone.prevY;

//     // current distance between missile and drone
//     float dx0 = drone.x - missile.x;
//     float dy0 = drone.y - missile.y;
//     float distance = sqrt(dx0 * dx0 + dy0 * dy0);

//     float missileSpeed =
//         sqrt(missile.velX * missile.velX +
//              missile.velY * missile.velY);

//     float t = distance / (missileSpeed * 10.0f);
//     // if(t < 1.0f) t = 1.0f; // Ensure prediction time is non-negative
//     if (t > 5.0f)
//         t = 5.0f; // Limit prediction time to prevent overshooting

//     float futureX = drone.x + velX * t;
//     float futureY = drone.y + velY * t;

//     std::cout << "t: " << t
//               << " futureX: " << futureX
//               << " futureY: " << futureY << std::endl;

//     // TARGET ANGLE ------------------------------------------------------
//     float dx = futureX - missile.x;
//     float dy = futureY - missile.y;
//     // float currentAngle = missile.angle;

//     float targetAngle = atan2(dy, dx);

//     float angleDiff = angleDifference(targetAngle, missile.angle);

//     // float t = 20.0f;

//     // float futureX = drone.x + velX * t;
//     // float futureY = drone.y + velY * t;

//     // float dirX = futureX - missile.x;
//     // float dirY = futureY - missile.y;

//     // TURNING ------------------------------------------------------
//     //  float gain = 3.0f;

//     // float turn = gain * angleDiff;

//     // float maxTurn = 0.03f;

//     // if(turn > maxTurn) turn = maxTurn;
//     // if(turn < -maxTurn) turn = -maxTurn;

//     // PID -------------------------------------------------------------
//     float kp = 5.0f; // Proportional gain
//     float kd = 4.0f; // Derivative gain
//     float ki = 0.0f; // Integral gain

//     float error = angleDifference(targetAngle, missile.angle);

//     // Derivative term
//     float derivative = error - missile.prevError;

//     // Integral term
//     missile.integralError += error;

//     float maxIntegral = 5.0f;

//     if (missile.integralError > maxIntegral)
//         missile.integralError = maxIntegral;

//     if (missile.integralError < -maxIntegral)
//         missile.integralError = -maxIntegral;

//     // PID output
//     float angularAccel = kp * error + kd * derivative + ki * missile.integralError;
//     std::cout << "Error: " << error
//               << " Derivative: " << derivative
//               << " Integral: " << missile.integralError
//               << " Angular Accel: " << angularAccel << std::endl;

//     // Update previous error for next iteration
//     missile.prevError = error;

//     // missile.angle += turn;

//     // angular accleration
//     //  float angularAccel = gain * angleDiff;

//     float maxAngularAccel = 0.01f;
//     if (angularAccel > maxAngularAccel)
//         angularAccel = maxAngularAccel;
//     if (angularAccel < -maxAngularAccel)
//         angularAccel = -maxAngularAccel;

//     missile.angularVel += angularAccel;

//     float angularDrag = 0.98f;
//     missile.angularVel *= angularDrag;

//     float maxAngularVel = 0.08f;
//     if (missile.angularVel > maxAngularVel)
//         missile.angularVel = maxAngularVel;
//     if (missile.angularVel < -maxAngularVel)
//         missile.angularVel = -maxAngularVel;

//     missile.angle += missile.angularVel;

//     // PHYSICS ------------------------------------------------------
//     applyPhysics(missile);

//     // MOVEMENT ------------------------------------------------------

//     // NOW HANDLES IN PHYSICS > motion.cpp
//     //  missile.velX = cos(missile.angle) * missile.speed;
//     //  missile.velY = sin(missile.angle) * missile.speed;

//     // float length = sqrt(dirX * dirX + dirY * dirY);

//     // if (length > 0.0001f) {
//     //     dirX /= length;
//     //     dirY /= length;
//     // }

//     // missile.x += missile.velX;
//     // missile.y += missile.velY;
// }
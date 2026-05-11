#include "pid.h"
#include <cmath>

float updatePID(PID &pid, float error)
{
    // Update integral term
    pid.integral += error;

    float maxIntegral = 100.0f; // Prevent integral windup
    if (pid.integral > maxIntegral)
        pid.integral = maxIntegral;
    else if (pid.integral < -maxIntegral)
        pid.integral = -maxIntegral;

    float derivative = error - pid.prevError;
    pid.prevError = error;

    float output = pid.kp * error + pid.ki * pid.integral + pid.kd * derivative;

    pid.prevError = error;

    return output;
}
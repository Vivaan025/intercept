#pragma once

struct PID
{
    float kp; // Proportional gain
    float ki; // Integral gain
    float kd; // Derivative gain

    float integral; // Integral term
    float prevError; // Previous error for derivative calculation
};

float updatePID(PID& pid, float error);

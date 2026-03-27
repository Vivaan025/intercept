#include <cmath>
// #include <corecrt_math_defines.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

float wrapAngle(float angle)
{
    angle = fmod(angle + M_PI, 2 * M_PI);
    if (angle < 0)
        angle += 2 * M_PI;
    return angle - M_PI;
}

float angleDifference(float targetAngle, float currentAngle)
{
    float diff = wrapAngle(targetAngle - currentAngle);
    return diff;
}
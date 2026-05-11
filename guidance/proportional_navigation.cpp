#include "proportional_navigation.h"

float proportionalNavigation(
    float missileSpeed,
    float losRate,
    float navigationConstant)
{
    return navigationConstant * missileSpeed * losRate;
}
#pragma once

#include <vector>

#include "../entities/trail_point.h"

void initRenderer();
void drawObject(float x, float y, float colorR, float colorG, float colorB);
void drawTrail(const std::vector<TrailPoint> &trail, float colorR, float colorG, float colorB);
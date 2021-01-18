#include <glm/glm.hpp>
#pragma once
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

namespace MathUtils {
	int getRandomNumber(int from, int to);

	float findDistance(float x1, float y1, float x2, float y2);
}

#endif // MATH_UTILS_H
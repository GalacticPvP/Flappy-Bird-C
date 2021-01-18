#include <random>
#include <iostream>
#include <time.h>
#include "MathUtils.h"
int MathUtils::getRandomNumber(int from, int to) {
	if (to - from == 0) {
		return from;
	}
	unsigned int seed = time(NULL);
	srand(seed);
	int number = rand() % (to - from) + from;
	return number;
}

float MathUtils::findDistance(float x1, float y1, float x2, float y2) {
	return (x1 - x2) - (y1 - y2);
}
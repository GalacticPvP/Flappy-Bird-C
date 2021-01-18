#pragma once
#ifndef VECTOR_H
#define VECTOR_H

class SpeedComponent {
public:
	float xSpeed, ySpeed, yAcceleration, xAcceleration;
	SpeedComponent(float xSpeed, float ySpeed, float yAcceleration, float xAcceleration);
};

#endif //SPEED_COMPONENT_H

#include "SpeedComponent.h"
#include "Texture.h"

#pragma once
#ifndef PIPE_H
#define PIPE_H


class Pipe {
private:
	Texture* texture;
public:
	float width, height, x, y;
	SpeedComponent* vector;

public:
	Pipe(float width, float height, float x, float y);
	~Pipe();

	bool scored;
	bool isOutOfRange();
	void render();
};

#endif //PLAYER_H
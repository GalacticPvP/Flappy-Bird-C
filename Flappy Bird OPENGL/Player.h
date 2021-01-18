#include "SpeedComponent.h"
#include "GameData.h"
#include "RenderUtils.h"
#include "Texture.h"

#pragma once
#ifndef PLAYER_H
#define PLAYER_H

struct Player {
private:
	Texture* texture;
	float radius;

public:
	float x, y;
	int score;

public:

	Player(float radius);
	~Player();

	float getDiameter();

	float getRadius();

	void render();
};

#endif //PLAYER_H
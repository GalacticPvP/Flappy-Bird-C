#include <iostream>
#include "Player.h"
#include "SpeedComponent.h"
#include "GameData.h"
#include "RenderUtils.h"

Player::Player(float radius) {
	this->radius = radius;
	this->x = 0;
	this->y = 0;
	this->score = 0;
	this->texture = new Texture("flappy.png");
}

Player::~Player() {
	if (score > GameData::getHighScore()) {
		GameData::setHighScore(score);
	}
	delete texture;
}

float Player::getDiameter() {
	return radius * 2;
}

float Player::getRadius() {
	return radius;
}

void Player::render() {
	//RenderUtils::drawCircle(GameData::getWindow(), x, y, 0, radius, 250, RGBColor(239.0f / 255.0f, 1.0f, 0.0f, 1.0f));
	Texture& ref = *texture;
	RenderUtils::renderImage(GameData::getWindow(), radius, radius, x, y, ref);
}
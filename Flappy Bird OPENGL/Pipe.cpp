#include <iostream>
#include "Pipe.h"
#include "RenderUtils.h"
#include "GameData.h"

Pipe::Pipe(float width, float height, float x, float y) {
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	this->scored = 0;
	this->vector = new SpeedComponent(-10.0f, 0.0f, 0.0f, 0.0f);
	this->texture = new Texture("pipe.png");
}

Pipe::~Pipe() {
	delete texture;
	delete vector;
}

bool Pipe::isOutOfRange() {
	return width + x <= -GameData::getWindowWidth();
}

void Pipe::render() {
	Texture& ref = *texture;
	if (y < 0) {
		RenderUtils::renderImage(GameData::getWindow(), width, height, x, y, ref);
	}
	else {
		float vertices[8] = { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f };
		RenderUtils::renderImage(GameData::getWindow(), width, height, x, y, ref, vertices);
	}
	//RenderUtils::drawRect(GameData::getWindow(), width, height, x, y, RGBColor((float)97 / 255, (float)1, (float)69 / 255, (float)1));
}
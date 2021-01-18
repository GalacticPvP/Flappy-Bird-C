#include <GLFW/glfw3.h>

#pragma once
#ifndef GAME_DATA_H
#define GAME_DATA_H

namespace GameData {
	void init();

	int getWindowWidth();
	int getWindowHeight();

	int getHighScore();
	void setHighScore(int score);

	GLFWwindow* getWindow();
}

#endif //GAME_DATA_H

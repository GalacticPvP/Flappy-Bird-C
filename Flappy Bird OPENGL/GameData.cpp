#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include "GameData.h"
#include "File.h"

GLFWwindow* window;
File* file;

void GameData::init() {
	window = glfwCreateWindow(800, 800, "Flappy Bird Game", NULL, NULL);
	int width;
	int height;
	glfwGetWindowSize(window, &width, &height);
	glfwSetWindowPos(window, 1920 / 2 - width / 2, 1080 / 2 - height / 2);
	file = new File("data.txt");
}

GLFWwindow* GameData::getWindow() {
	return window;
}

int GameData::getHighScore() {
	File& referenceFile = *file;
	int index = referenceFile.findLineStartsWith("Score: ");
	if (index == -1) {
		return 0;
	}
	std::string line = referenceFile.getLine(index);
	std::string subValue = line.substr(7, line.length());
	int value = std::stoi(subValue);
	return value;
}

void GameData::setHighScore(int score) {
	File& referenceFile = *file;
	int index = referenceFile.findLineStartsWith("Score: ");
	std::string toInsert = "Score: " + std::to_string(score);
	referenceFile.set(index == -1 ? 0 : index, toInsert.c_str());
}

int GameData::getWindowWidth() {
	int width;
	int height;
	glfwGetWindowSize(window, &width, &height);
	return width;
}

int GameData::getWindowHeight() {
	int width;
	int height;
	glfwGetWindowSize(window, &width, &height);
	return height;
}
#include <GL/glew.h>
#include <vector>
#include <list>
#include <iostream>
#include <ctime>
#include <math.h>
#include <sys/timeb.h>
#include <Windows.h>
#include <GLM/glm.hpp>
#include "RenderUtils.h"
#include "Player.h"
#include "Pipe.h"
#include "GameData.h"
#include "MathUtils.h"
#include "Shader.h"
#include "FontRenderer.h"
#include "RGBColor.h"

Player* player;
std::vector<Pipe*> pipes;
double last_space_bar;
boolean gameRunning;
FontRenderer* textRenderer;
Texture* background;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE) {
        if (!gameRunning) {
            gameRunning = true;
        }
        Player& pl = *player;
        pl.y = std::min((float)GameData::getWindowHeight(), (float)(pl.y + 50));
        last_space_bar = glfwGetTime();
    }
}

void init() {
    glfwSetKeyCallback(GameData::getWindow() , key_callback);
    player = new Player(75);
    RenderUtils::setupShader();
    textRenderer = new FontRenderer("C:/Windows/Fonts/arial.ttf", 50);
    background = new Texture("background.jpeg");
}

bool isGameRunning() {
    return gameRunning;
}

void clearPipes() {
	for (int i = pipes.size() - 1; i >= 0; i--) {
		Pipe* pointer = pipes[i];
		Pipe& pipe = *pointer;
		delete pointer;
		pipes.erase(pipes.begin() + i);
	}
}

void renderScore() {
	std::string text = std::to_string(player->score);
	int offset = (GameData::getWindowWidth() - textRenderer->getLengthOfString(text, 1.0f)) / 2;
    textRenderer->renderText(RenderUtils::getFontShader(), text, offset, GameData::getWindowHeight() - 50.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    if (!isGameRunning()) {
        text = "High Score: " + std::to_string(GameData::getHighScore());
        offset = (GameData::getWindowWidth() - textRenderer->getLengthOfString(text, 2.0f)) / 2;
        textRenderer->renderText(RenderUtils::getFontShader(), text, offset,
        GameData::getWindowHeight() - 250.0f, 2.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    }
}

void renderGameText() {
    textRenderer->renderText(RenderUtils::getFontShader(), "Flappy Bird v0.1", 0, GameData::getWindowHeight() - 25.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void renderBackground() {
    Texture& bg = *background;
    RenderUtils::renderImage(GameData::getWindow(), GameData::getWindowWidth() * 2, GameData::getWindowHeight(), 0, 0, bg);
}

void reset() {
    delete player;
    player = new Player(75);
    clearPipes();
    gameRunning = false;
}

void refreshPipes() {
	bool canSpawn = pipes.size() == 0 ? true : false;
	for (int i = pipes.size() - 1; i >= 0; i--) {
		Pipe* pointer = pipes[i];
		Pipe& pipe = *pointer;
		if (gameRunning) {
			pipe.x = pipe.x + (*(pipe).vector).xSpeed;
		}
		pipe.render();
		if (pipe.isOutOfRange()) {
			delete pointer;
			pipes.erase(pipes.begin() + i);
			continue;
		}
	}
	if (pipes.size() > 0) {
		if (GameData::getWindowWidth() / 2 - (*pipes.at(pipes.size() - 1)).x >= 250) {
			canSpawn = true;
		}
	}
	int minimumDistance = 300;
	if (canSpawn) {
		int maximumSpace = 1250;
		int minimumSpace = 750;
		float factor = MathUtils::getRandomNumber(165, 200) * 0.01f;
		int heightOne = MathUtils::getRandomNumber(minimumSpace / factor, maximumSpace / factor);
		maximumSpace -= heightOne;
		minimumSpace -= heightOne;
		int heightTwo = maximumSpace * MathUtils::getRandomNumber(75, 100) * 0.01;
		Pipe* pipe_one;
		pipe_one = new Pipe(75, heightTwo, GameData::getWindowWidth(), -GameData::getWindowHeight());
		Pipe* pipe_two;
		pipe_two = new Pipe(75, heightOne, GameData::getWindowWidth(), GameData::getWindowHeight());
		pipes.push_back(pipe_one);
		pipes.push_back(pipe_two);
	}
}

void gameLoop() {
    renderBackground();
    refreshPipes();
    renderScore();
    renderGameText();
    Player& pl = *player;
    if (last_space_bar - glfwGetTime() + 0.1 <= 0 && gameRunning) {
        pl.y = std::max((float) -GameData::getWindowHeight(), (float) pl.y - 10);
    }
    pl.render();
    if (isGameRunning) {
        for (Pipe* pointer : pipes) {
            Pipe& pipe = *pointer;
            if (pipe.x - pipe.width <= pl.x + pl.getRadius() && pipe.x + pipe.width >= pl.x - pl.getRadius() ||
                pipe.x - pipe.width >= pl.x - pl.getRadius() && pipe.x + pipe.width <= pl.x - pl.getRadius()) {
                if (pipe.y <= 0) {
                    if (pipe.y + pipe.height >= pl.y - pl.getRadius()) {
                        reset();
                    }
                }
                else {
                    if (pipe.y - pipe.height <= pl.y + pl.getRadius()) {
                        reset();
                    }
                }
            }
            if (!pipe.scored && pipe.y > 0) {
                if (pipe.x + pipe.width <= pl.x + pl.getRadius()) {
                    pl.score++;
                    pipe.scored = true;
                }
            }
        }
    }
}

int main(void)
{
    if (!glfwInit()) {
        std::cout << "GLFW FAILED TO START" << std::endl;
        return -1;
    }
    GameData::init();
    if (!GameData::getWindow())
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(GameData::getWindow());
    glfwSwapInterval(1);
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW FAILED TO START" << std::endl;
        return -1;
    }
    init();
    while (!glfwWindowShouldClose(GameData::getWindow()))
    {
        glClear(GL_COLOR_BUFFER_BIT);
		gameLoop();
        glfwSwapBuffers(GameData::getWindow());
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
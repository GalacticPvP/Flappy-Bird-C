#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <math.h>
#include "RenderUtils.h"
#include "RGBColor.h"
#include "GameData.h"
#include "MathUtils.h"
#include "ShaderProgramSource.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
static Shader* shader;
static Shader* fontShader;
static Shader* textureShader;

void RenderUtils::color(float red, float green, float blue, float alpha) {
	getShader().setUniform4f("u_Color", red, green, blue, alpha);
}

void RenderUtils::color(RGBColor color) {
	RenderUtils::color(color.red, color.green, color.blue, color.alpha);
}

Shader& RenderUtils::getFontShader() {
	return *fontShader;
}

Shader& RenderUtils::getShader() {
	return *shader;
}

Shader& RenderUtils::getTextureShader() {
	return *textureShader;
}

void RenderUtils::setupShader() {
	shader = new Shader("res/shaders/Basic.shader");
	fontShader = new Shader("res/shaders/Font.shader");
	textureShader = new Shader("res/shaders/Texture.shader");
}

void RenderUtils::renderImage(GLFWwindow* window, float width, float height, float x, float y, Texture& texture, float imageVertices[8]) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	RenderUtils::getTextureShader().bind();
	RenderUtils::getTextureShader().setUniform1i("u_Texture", 0);
	texture.bind();
	x /= (float)GameData::getWindowWidth();
	y /= (float)GameData::getWindowHeight();
	width /= (float)GameData::getWindowWidth();
	height /= (float)GameData::getWindowHeight();
	float positions[] = {
		x - width, y + height, imageVertices[0], imageVertices[1],
		x - width, y - height, imageVertices[2], imageVertices[3],
		x + width, y - height, imageVertices[4], imageVertices[5],
		x + width, y + height, imageVertices[6], imageVertices[7]
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	VertexArray va;
	VertexBuffer vb(positions, 4 * 4 * sizeof(float));
	VertexBufferLayout layout;
	layout.push<float>(2);
	layout.push<float>(2);
	va.addBuffer(vb, layout);
	va.bind();
	IndexBuffer ib(indices, 6);
	ib.bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glDisable(GL_BLEND);
	ib.unbind();
	va.unbind();
	vb.unbind();
	texture.unbind();
	RenderUtils::getTextureShader().unbind();
}

void RenderUtils::renderImage(GLFWwindow* window, float width, float height, float x, float y, Texture& texture) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	RenderUtils::getTextureShader().bind();
	RenderUtils::getTextureShader().setUniform1i("u_Texture", 0);
	texture.bind();
	x /= (float)GameData::getWindowWidth();
	y /= (float)GameData::getWindowHeight();
	width /= (float)GameData::getWindowWidth();
	height /= (float)GameData::getWindowHeight();
	float positions[] = {
		x - width, y + height, 0.0f, 1.0f,
		x - width, y - height, 0.0f, 0.0f,
		x + width, y - height, 1.0f, 0.0f,
		x + width, y + height, 1.0f, 1.0f
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	VertexArray va;
	VertexBuffer vb(positions, 4 * 4 * sizeof(float));
	VertexBufferLayout layout;
	layout.push<float>(2);
	layout.push<float>(2);
	va.addBuffer(vb, layout);
	va.bind();
	IndexBuffer ib(indices, 6);
	ib.bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glDisable(GL_BLEND);
	ib.unbind();
	va.unbind();
	vb.unbind();
	texture.unbind();
	RenderUtils::getTextureShader().unbind();
}

void RenderUtils::drawRect(GLFWwindow* window, float width, float height, float x, float y, RGBColor color) {
	glEnable(GL_BLEND);
	glBlendFunci(0, GL_SRC_ALPHA, GL_ONE);
	shader->bind();
	RenderUtils::color(color);
	x /= (float)GameData::getWindowWidth();
	y /= (float)GameData::getWindowHeight();
	width /= (float)GameData::getWindowWidth();
	height /= (float)GameData::getWindowHeight();
	float positions[] = {
		x - width, y + height,
		x - width, y - height,
		x + width, y - height,
		x + width, y + height
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	VertexArray va;
	VertexBuffer vb(positions, 4 * 2 * sizeof(float));
	VertexBufferLayout layout;
	layout.push<float>(2);
	va.addBuffer(vb, layout);
	va.bind();
	IndexBuffer ib(indices, 6);
	ib.bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glDisable(GL_BLEND);
	ib.unbind();
	va.unbind();
	vb.unbind();
	shader->unbind();
}

void RenderUtils::drawCircle(GLFWwindow* window, float x, float y, float z, float radius, int sides, RGBColor color) {
	glEnable(GL_BLEND);
	glBlendFunci(0, GL_SRC_ALPHA, GL_ONE);
	shader->bind();
	RenderUtils::color(color);
	x /= GameData::getWindowWidth();
	y /= GameData::getWindowHeight();
	radius = radius / ((GameData::getWindowWidth() + GameData::getWindowHeight()) / (float)2);
	int vertices = sides + 2;
	float doublePI = 2.0f * 3.14159f;
	float* verticesX = (float*)alloca(vertices * sizeof(float));
	float* verticesY = (float*)alloca(vertices * sizeof(float));
	float* verticesZ = (float*)alloca(vertices * sizeof(float));
	verticesX[0] = x;
	verticesY[0] = y;
	verticesZ[0] = z;
	for (int i = 1; i < vertices; i++) {
		verticesX[i] = (float)(x + (radius * cos(i * doublePI / sides)));
		verticesY[i] = (float)(y + (radius * sin(i * doublePI / sides)));
		verticesZ[i] = z;
	}
	int verticeLength = 3;
	float* allVertices = (float*)alloca(vertices * verticeLength * sizeof(float));
	for (int i = 0; i < vertices; i++) {
		allVertices[i * verticeLength] = (float)verticesX[i];
		allVertices[i * verticeLength + 1] = (float)verticesY[i];
		allVertices[i * verticeLength + 2] = (float)verticesZ[i];
	}
	VertexArray va;
	VertexBuffer vb(allVertices, vertices * verticeLength * sizeof(float));
	VertexBufferLayout layout;
	layout.push<float>(3);
	va.addBuffer(vb, layout);
	va.bind();
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertices);
	glDisable(GL_BLEND);
	va.unbind();
	vb.unbind();
	shader->unbind();
}
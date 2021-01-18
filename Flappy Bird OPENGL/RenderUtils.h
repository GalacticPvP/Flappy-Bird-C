#include <GLFW/glfw3.h>
#include "RGBColor.h"
#include "ShaderProgramSource.h"
#include "Shader.h"
#include "Texture.h"


#pragma once
#ifndef RENDER_UTILS_H
#define RENDER_UTILS_H

namespace RenderUtils {

    void color(float red, float green, float blue, float alpha);

    void color(RGBColor color);

    void setupShader();

    void renderImage(GLFWwindow* window, float width, float height, float x, float y, Texture& texture);
    void renderImage(GLFWwindow* window, float width, float height, float x, float y, Texture& texture, float imageVertices[8]);

    void drawRect(GLFWwindow* window, float width, float height, float x, float y, RGBColor color);

    void drawCircle(GLFWwindow* window, float x, float y, float z, float radius, int sides, RGBColor color);

    Shader& getShader();
    Shader& getFontShader();
    Shader& getTextureShader();
}
#endif // RENDER_UTILS_H
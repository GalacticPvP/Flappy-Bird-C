#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include "Shader.h"

#pragma once
#ifndef FONT_RENDERER_H
#define FONT_RENDERER_H


class FontRenderer {
private:
	FT_Face face;
	FT_Library ft;
	const char* const fileName;

public:
	int fontSize;

public:
	FontRenderer(const char* const file, int fontSize);
	~FontRenderer();
	void loadFile(const char* const fileName, int fontSize);
	void setFontSize(int fontSize) {
		this->fontSize = fontSize;
		FT_Set_Pixel_Sizes(face, 0, fontSize);
	}
	void loadGlyphs();
	void renderText(Shader& s, std::string text, float x, float y, float scale, glm::vec3 color);

	int getLengthOfString(std::string& text, int scale);
};

#endif //FONT_RENDERER_H

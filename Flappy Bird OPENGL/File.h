#include <string>
#pragma once
#ifndef FONT_H
#define FONT_H

class File {
public:
	const char* fileName;

public:
	File(const char* fileName);
	~File();

	std::string getLine(int line);

	void insert(const char* text);
	void set(int line, const char* text);

	int findLineStartsWith(const char* text);
};

#endif //FONT_H
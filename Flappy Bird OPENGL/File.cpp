#include <fstream>
#include <iostream>
#include "File.h"


File::File(const char* fileName) {
	this->fileName = fileName;
	std::fstream stream;
	stream.open(fileName, std::fstream::in | std::fstream::out | std::fstream::app);
	if (!stream) {
		std::cout << "Creating file '" << fileName << "'" << std::endl;
		stream.open(fileName, std::fstream::in | std::fstream::out | std::fstream::app);
		stream << "\n";
		stream.close();
	}
}

std::string File::getLine(int index) {
	std::ifstream stream;
	stream.open(fileName);
	std::string line;
	while (getline(stream, line)) {
		if (index-- == 0) {
			stream.close();
			return line;
		}
	}
	stream.close();
}

int File::findLineStartsWith(const char* text) {
	std::ifstream stream;
	stream.open(fileName);
	std::string line;
	int index = 0;
	while (getline(stream, line)) {
		if (line.rfind(text) == 0) {
			stream.close();
			return index;
		}
		index++;
	}
	stream.close();
	return -1;
}

void File::set(int index, const char* text) {
	std::ofstream stream;
	stream.open(fileName);
	std::string line;
	for (int i = 0; i < index; i++) {
		stream << "\n";
	}
	stream << text;
	stream.close();
}

void File::insert(const char* text) {
	std::fstream stream;
	stream.open(fileName, std::fstream::out);
	std::string line;
	while (getline(stream, line)) {
		stream << "\n";
	}
	stream << text;
	stream.close();
}
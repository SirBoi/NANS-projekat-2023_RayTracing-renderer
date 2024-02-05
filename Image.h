#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include "Color.h"
#pragma once

struct Image {
	int height;
	int width;
	int currentHeight;
	int currentWidth;
	double aspectRatio;
	std::string name;
	std::vector<std::vector<Color>> pixels;

	Image();
	Image(int, int);
	Image(int, int, std::string);
	Image(int, int, std::string, std::string);

	void createPNG();
	void writePixel(Color);
};
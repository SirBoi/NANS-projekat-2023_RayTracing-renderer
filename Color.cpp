#include "Color.h"

Color::Color() : r(0), g(0), b(0) {
	r = 0;
	g = 0;
	b = 0;
};

Color::Color(double r, double g, double b) : r(r), g(g), b(b) {};

Color::Color(std::string colorName) : r(0), g(0), b(0) {
	if (colorName == "black") {
		r = 0; g = 0; b = 0;
	}
	else if (colorName == "white") {
		r = 255; g = 255; b = 255;
	}
	else if (colorName == "red") {
		r = 255; g = 0; b = 0;
	}
	else if (colorName == "green") {
		r = 0; g = 255; b = 0;
	}
	else if (colorName == "blue") {
		r = 0; g = 0; b = 255;
	}
	else if (colorName == "yellow") {
		r = 255; g = 255; b = 0;
	}
	else if (colorName == "magenta") {
		r = 255; g = 0; b = 255;
	}
	else if (colorName == "cyan") {
		r = 0; g = 255; b = 255;
	}
};

Color Color::operator+(Color c) {
	return Color(r + c.r, g + c.g, b + c.b);
};
Color Color::operator*(double d) {
	return Color(r * d, g * d, b * d);
};
Color Color::operator*(Color c) {
	return Color(r * c.r, g * c.g, b * c.b);
};
Color Color::operator/(double d) {
	return Color(r / d, g / d, b / d);
};
std::ostream& operator<<(std::ostream& os, Color c) {
	os << c.r << " " << c.g << " " << c.b << "\n";
	return os;
};
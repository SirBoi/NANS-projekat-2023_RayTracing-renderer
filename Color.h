#include <string>
#include <iostream>
#pragma once

struct Color {
	double r;
	double g;
	double b;

	Color();
	Color(double, double, double);
	Color(std::string);

	Color operator+(Color);
	Color operator*(double);
	Color operator*(Color);
	Color operator/(double);
	friend std::ostream& operator<<(std::ostream&, Color);
};
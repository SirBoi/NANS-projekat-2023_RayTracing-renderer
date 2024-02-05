#include "Util.h"
#include <random>

double degToRad(double degrees) {
    return degrees * pi / 180.0;
}

double randomDouble() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}
#define _CRT_SECURE_NO_DEPRECATE

#include "Image.h"

Image::Image() : height(720), width(1280), currentHeight(0), currentWidth(0), aspectRatio(1.7778), name("image") {
    std::vector<std::vector<Color>> rows;

    for (int i = 0; i < height; ++i) {
        std::vector<Color> row;

        for (int j = 0; j < width; ++j) {
            row.push_back(Color("black"));
        }
        rows.push_back(row);
    }
    pixels = rows;
};

Image::Image(int height, int width) : height(height), width(width), currentHeight(0), currentWidth(0), name("image") {
    aspectRatio = double(width) / height;

    std::vector<std::vector<Color>> rows;

    for (int i = 0; i < height; ++i) {
        std::vector<Color> row;

        for (int j = 0; j < width; ++j) {
            row.push_back(Color("black"));
        }
        rows.push_back(row);
    }
    pixels = rows;
};

Image::Image(int height, int width, std::string colorName) : height(height), width(width), currentHeight(0), currentWidth(0), name("image") {
    aspectRatio = double(width) / height;

    std::vector<std::vector<Color>> rows;

    for (int i = 0; i < height; ++i) {
        std::vector<Color> row;

        for (int j = 0; j < width; ++j) {
            row.push_back(Color(colorName));
        }
        rows.push_back(row);
    }
    pixels = rows;
};

Image::Image(int height, int width, std::string colorName, std::string name) : height(height), width(width), currentHeight(0), currentWidth(0), name(name) {
    aspectRatio = double(width) / height;

    std::vector<std::vector<Color>> rows;

    for (int i = 0; i < height; ++i) {
        std::vector<Color> row;

        for (int j = 0; j < width; ++j) {
            row.push_back(Color(colorName));
        }
        rows.push_back(row);
    }
    pixels = rows;
};

void Image::createPNG() {
    std::ofstream output("slike\\image.ppm", std::ios::binary);

    if (output.is_open()) {
        output << "P3\n" << width << ' ' << height << "\n255\n";

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                Color color = pixels[i][j];

                output << static_cast<int>(255.999 * sqrt(color.r)) << " " << static_cast<int>(255.999 * sqrt(color.g)) << " " << static_cast<int>(255.999 * sqrt(color.b)) << "\n";
            }
        }
        output.close();
    }
    else {
        perror("\nError occured while oppening file image.ppm.   ");
    }

    try {
        system("python convert.pyw");
    }
    catch (...) {
        perror("\nError occured while attempting to run convert.pyw. Make sure you have python and its pillow library installed.   ");
    }
    
    std::string newName = "slike\\" + name + ".jpg";

    time_t timet = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string datetime = ctime(&timet);
    if (datetime[9] == ' ')
        datetime = datetime.substr(0, 7) + '0' + datetime.substr(8);
    datetime = datetime.substr(8, 2) + "-" + datetime.substr(4, 3) + "-" + datetime.substr(20, 4) + "_" + datetime.substr(11, 2) + "-" + datetime.substr(14, 2) + "-" + datetime.substr(17, 2);

    if (rename("slike\\image.jpg", ("slike\\" + name + "_" + datetime + ".jpg").c_str()) != 0)
        perror("\nError occured while renaming file image.ppm.   ");
    std::remove("slike\\image.ppm");
};

void Image::writePixel(Color color) {
    pixels[currentHeight][currentWidth] = color;

    currentWidth++;

    if (currentWidth == width) {
        currentHeight++;
        currentWidth = 0;
    }
}
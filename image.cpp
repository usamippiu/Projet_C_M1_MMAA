#include "image.h"
#include "pixel.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

// Charger une image
void PPMImage::PPMImageLoader(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    unsigned int lineCount = 0;
    while (std::getline(file, line)) {
        if (line[0] == '#')
            continue;

        std::istringstream iss(line);

        if (lineCount == 1){
            iss >> width >> height;
            pixels.resize(width * height);
        }
        if (lineCount == 2){
            iss >> maxColor;
        }

        if (lineCount > 3){
            for (unsigned i = 0; i < 900; ++i) {
                std::getline(file, line);
                pixels[i].r = std::stoi(line);
                std::getline(file, line);
                pixels[i].g = std::stoi(line);
                std::getline(file, line);
                pixels[i].b = std::stoi(line);
            }
            break;
        }

        lineCount++;
    }

    file.close();
}

// avoir la taille de l'image :
int PPMImage::getWidth() const {
    return this->width;
}

int PPMImage::getHeight() const {
    return this->height;
}

// Avoir le pixel à telles coordonnées de l'image
Pixel PPMImage::getPixel(int x, int y) const {
    return this->pixels[y * this->width + x];
}

// Ecriture dans une image

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

    // iteration sur les lignes
    while (std::getline(file, line)) {
        if (line[0] == '#')
            continue;

        std::istringstream iss(line);

        // Dans les ppm la taille de l'image se trouve en ligne 1
        if (lineCount == 1){
            iss >> width >> height;
            this->width = width;
            this->height = height;
            this->pixels.resize(width * height);
        }
        if (lineCount == 2){
            iss >> maxColor;
            this->maxColor = maxColor;
        }

        if (lineCount > 3){
            for (unsigned i = 0; i < width * height - 1; ++i) {
                std::getline(file, line);
                this->pixels[i].r = std::stoi(line);
                std::getline(file, line);
                this->pixels[i].g = std::stoi(line);
                std::getline(file, line);
                this->pixels[i].b = std::stoi(line);
            }
            break;
        }

        lineCount++;
    }

    file.close();
}

// Avoir la taille de l'image :
int PPMImage::getWidth() const {
    return this->width;
}

int PPMImage::getHeight() const {
    return this->height;
}

int PPMImage::getMaxColor() const{
    return this->maxColor;
}

// Avoir le pixel à telles coordonnées de l'image
Pixel PPMImage::getPixel(int x, int y) const {
    return this->pixels[y * this->width + x];
}

// Ecriture dans une image

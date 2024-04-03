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


        if (lineCount == 1){
            std::istringstream iss(line);
            iss >> width >> height;
            pixels.resize(width * height);
        }
        if (lineCount == 2){
            std::istringstream iss(line);
            iss >> maxColor;
        }

        if (lineCount >= 3){
            for (unsigned i = 0; i < width*height; ++i) {
                pixels[i].r = std::stoi(line);
                std::cout <<pixels[i].r << std::endl;
                std::getline(file, line);
                pixels[i].g = std::stoi(line);
                std::cout <<pixels[i].g << std::endl;
                std::getline(file, line);
                pixels[i].b = std::stoi(line);
                std::cout <<pixels[i].b << std::endl;
                std::getline(file, line);
                std::cout << i << " " << pixels[i].r << " " <<pixels[i].g << " " <<pixels[i].b << std::endl;
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

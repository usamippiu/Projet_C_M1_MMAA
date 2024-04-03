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

        if (lineCount >= 3){
            for (unsigned i = 0; i < width*height; ++i) {
                this->pixels[i].r = std::stoi(line);
                //std::cout <<this->pixels[i].r << std::endl;
                std::getline(file, line);
                this->pixels[i].g = std::stoi(line);
                //std::cout <<this->pixels[i].g << std::endl;
                std::getline(file, line);
                this->pixels[i].b = std::stoi(line);
                //std::cout <<this->pixels[i].b << std::endl;
                std::getline(file, line);
                //std::cout << " " << this->pixels[i].r << " " << this->pixels[i].g << " " <<this->pixels[i].b << std::endl;
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
//Pixel PPMImage::getPixel(int x, int y) const {
//    return this->pixels[y * this->width + x].getPixel();
//}

// Conversion pixel vecteur ligne en matrice
std::vector<std::vector<Pixel>> PPMImage::convertTo2D(const std::vector<Pixel>& input, int height, int width) {
    std::vector<std::vector<Pixel>> output(height, std::vector<Pixel>(width));

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            output[i][j] = input[i * width + j];
        }
    }

    return output;
}

// Ecrire sur l'image

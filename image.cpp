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

        // Si on arrive à la troisième ligne alors on a les couleurs de nos pixel qu'on stock
        if (lineCount >= 3){
            for (unsigned i = 0; i < width*height; ++i) {
                this->pixels[i].r = std::stoi(line);
                std::getline(file, line);
                this->pixels[i].g = std::stoi(line);
                std::getline(file, line);
                this->pixels[i].b = std::stoi(line);
                std::getline(file, line);
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

// Afficher la matrice de Pixel
void PPMImage::afficheMatrice(std::vector<std::vector<Pixel>>&  input, int height, int width) {
    for(int i = 0; i < height; i++ )
    {
        for(int j = 0; j < width ; j++)
        {
            std::cout << "r " << input[i][j].getPixel()[0] << " g " << input[i][j].getPixel()[1] << " b " << input[i][j].getPixel()[2] << std::endl;
        }
    }
}

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

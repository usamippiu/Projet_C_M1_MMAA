#include "image.h"
#include "pixel.h"

#include <iostream>
#include <fstream>
#include <vector>

// Charger une image
void PPMImage::PPMImageLoader(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Erreur: Ouverture du fichier " << filename << std::endl;
        return;
    }

    std::string magic;
    file >> magic;
    if (magic != "P6") {
        std::cerr << "Erreur: Format du fichier " << std::endl;
        return;
    }

    file >> this->width >> this->height >> maxColor;
    file.ignore(256, '\n');

    this->pixels.resize(this->width * this->height);
    file.read(reinterpret_cast<char*>(this->pixels.data()), this->pixels.size() * sizeof(Pixel));

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
    return this->pixels[y * width + x];
}

// Ecriture dans une image

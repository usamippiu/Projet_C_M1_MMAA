#include "image.h"
#include "pixel.h"

#include <iostream>
#include <fstream>

// Charger une image
PPMImage::PPMImageLoader(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Erreur: Ouverture du fichier " << filename << std::endl;
        return;
    }

    std::string magic;
    file >> magic;
    if (magic != "P6") {
        std::cerr << "Erreur: Format du fichier" << std::endl;
        return;
    }

    file >> width >> height >> maxColor;
    file.ignore(256, '\n');

    pixels.resize(width * height);
    file.read(reinterpret_cast<char*>(pixels.data()), pixels.size() * sizeof(Pixel));

    file.close();
}

// avoir la taille de l'image :
int PPMImage::getWidth() const {
    return width;
}

int PPMImage::getHeight() const {
    return height;
}

// Avoir le pixel à telles coordonnées de l'image
Pixel PPMImage::getPixel(int x, int y) const {
    return pixels[y * width + x];
}

// Ecriture dans une image

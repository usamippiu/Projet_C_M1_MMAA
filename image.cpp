#include "image.h"
#include "pixel.h"

#include <iostream>
#include <fstream>
#include <vector>

// Charger une image
void PPMImage::PPMImageLoader(const std::string& filename) {

    std::ifstream file(filename);
    std::string line;
    std::vector<int> dimensions;
    std::string output;

    if (!file.is_open()) {
        std::cerr << "Erreur: Ouverture du fichier " << filename << std::endl;
        return;
    }

    std::string magic;
    file >> magic;
    if (magic != "P3") {
        std::cerr << "Erreur: Format du fichier" << std::endl;
        file.close();
        return;
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int i = 0;
    for(std::string ligne ; std::getline(file,ligne) ; ){
        std::stringstream fluxLigne(ligne);

        for(std::string mot ; std::getline(fluxLigne,mot, ' '); ){
            dimensions.push_back(std::stoi(mot));
        }

        if (i >= 3){
            Pixel pixelCourant;
            this->pixelCourant-> r = dimensions[0];
            this->pixelCourant-> g = dimensions[1];
            this->pixelCourant-> b = dimensions[2];
            this->pixel.push_back(pixelCourant);
        }
        i ++;

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

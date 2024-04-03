#ifndef _IMAGE_H_
#define _IMAGE_H_
#include "pixel.h"
#include <vector>
#include <string>

// image ppm = valeurs ligne par ligne
// indice i =0 = en haut à gauche de l'image etc
class PPMImage {
private:
    unsigned int width, height, maxColor;

public:
    std::vector<Pixel> pixels;
    void PPMImageLoader(const std::string& filename);
    int getWidth() const;
    int getHeight() const;
    int getMaxColor() const;
    void afficheMatrice(std::vector<std::vector<Pixel>>&  input, int height, int width);
    std::vector<std::vector<Pixel>> convertTo2D(const std::vector<Pixel>& input, int height, int width);


};

#endif

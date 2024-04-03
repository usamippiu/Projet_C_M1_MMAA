#include "image.h"
#include "pixel.h"

#include <iostream>
#include <fstream>
#include <vector>

void Pixel::setRGB(unsigned int r, unsigned int g, unsigned int b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

std::vector<unsigned int> Pixel::getPixel() {
    std::vector<unsigned int> colors = {this->r, this->g, this->b};
    return colors;
}

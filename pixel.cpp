#include "image.h"
#include "pixel.h"

#include <iostream>
#include <fstream>

void Pixel::setRGB(unsigned int r, unsigned int g, unsigned int b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

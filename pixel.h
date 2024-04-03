#ifndef _PIXEL_H_
#define _PIXEL_H_
#include <vector>

struct Pixel {
    unsigned int r, g, b;
    void setRGB(unsigned int r, unsigned int g, unsigned int b);
    std::vector<unsigned int> getPixel();

};

#endif

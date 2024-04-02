#ifndef _IMAGE_H_
#define _IMAGE_H_
#include "pixel.h"
#include <vector>
#include <string>
// image ppm = valeurs ligne par ligne
class PPMImage {
private:
    int width, height, maxColor;
    std::vector<Pixel> pixels;

public:
    void PPMImageLoader(const std::string& filename);
    int getWidth() const;
    int getHeight() const;
    Pixel getPixel(int x, int y) const;
};

#endif

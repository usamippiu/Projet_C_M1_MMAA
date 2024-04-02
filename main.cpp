#include "image.h"
#include "pixel.h"
#include <iostream>
#include <fstream>

using namespace std;
int main()
{

// Test de la classe image et ses méthodes
    PPMImage image;
    image.PPMImageLoader("imgSimple.ppm");

    int width = image.getWidth();
    int height = image.getHeight();
    //Pixel pixel = image.getPixel(0, 0);
    cout<< width << endl;
    cout<< height << endl;

}

#include "image.h"
#include "pixel.h"
#include <iostream>
#include <fstream>

using namespace std;
int main()
{

// Test de la classe image et ses méthodes
    PPMImage image;
    image.PPMImageLoader("m1projetcpp2.ppm");

    int width = image.getWidth();
    int height = image.getHeight();
    int maxColor = image.getMaxColor();
    //Pixel pixel = image.getPixel(0, 0);
    cout<< width << endl;
    cout<< height << endl;
    cout<<maxColor <<endl;
    //cout << image.pixels.getPixel() << endl;

}

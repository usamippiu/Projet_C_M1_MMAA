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
    cout<< "width = " << width << endl;
    cout<<"height =" << height << endl;
    cout<<"maxColor =" << maxColor <<endl;

    std::vector<std::vector<Pixel>> matrice_Pixel;
    matrice_Pixel = image.convertTo2D(image.pixels, height, width);
    for(int i = 0; i < height; i++ )
    {
        for(int j = 0; j < width ; j++)
        {
            cout << "r " << matrice_Pixel[i][j].getPixel()[0] << " g " << matrice_Pixel[i][j].getPixel()[1] << " b " << matrice_Pixel[i][j].getPixel()[2] << endl;
        }
    }
    //cout << image.pixels.getPixel() << endl;

}

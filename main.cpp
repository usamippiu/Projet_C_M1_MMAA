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
    cout<< "width = " << width << endl;
    cout<<"height =" << height << endl;
    cout<<"maxColor =" << maxColor <<endl;

    std::vector<std::vector<Pixel>> matrice_Pixel;
    matrice_Pixel = image.convertTo2D(image.pixels, height, width);
    image.afficheMatrice( matrice_Pixel, height, width);
    //image.MatriceToImage(matrice_Pixel, height, width, maxColor, "output.ppm");

    std::vector<float> eqDroite;
    eqDroite = image.equationDroite( 0, 0, 30, 30);
    image.tracerDroite( eqDroite, matrice_Pixel );
    image.MatriceToImage(matrice_Pixel, height, width, maxColor, "output.ppm");


}

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
    // setters et getters
    int width = image.getWidth();
    int height = image.getHeight();
    int maxColor = image.getMaxColor();
    cout<< "width = " << width << endl;
    cout<<"height =" << height << endl;
    cout<<"maxColor =" << maxColor <<endl;

    // Création de la matrice de pixel
    std::vector<std::vector<Pixel>> matrice_Pixel;
    matrice_Pixel = image.convertTo2D(image.pixels, height, width);
    image.afficheMatrice( matrice_Pixel, height, width);
    //image.MatriceToImage(matrice_Pixel, height, width, maxColor, "output.ppm");

    // Test tracer de droite
   // std::vector<float> eqDroite;
    //eqDroite = image.equationDroite( 0, 0, 30, 30);
    //image.tracerDroite( eqDroite, matrice_Pixel );
    //image.MatriceToImage(matrice_Pixel, height, width, maxColor, "output.ppm");

    // Test tracer de droite aux coordonnées polaires
    std::vector<float> eqDroitePolaire;
    eqDroitePolaire = image.equationDroitePolaire( 10, 30 );
    image.tracerDroitePolaire( eqDroitePolaire, matrice_Pixel );
    image.MatriceToImage(matrice_Pixel, height, width, maxColor, "output.ppm");



}

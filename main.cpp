#include "image.h"
#include "pixel.h"
#include <iostream>
#include <fstream>
#include<tuple>

void affiche_tuples(std::vector<std::tuple<double, double>>& tuples){
    std::cout << "------------------------" << std::endl;
    for (const auto& tuple : tuples) {
        std::cout << "(" << std::get<0>(tuple) << ", " << std::get<1>(tuple) << ")" << std::endl;
    }
}

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
    cout<< "height = " << height << endl;
    cout<< "maxColor = " << maxColor <<endl;

    // Création de la matrice de pixel
    std::vector<std::vector<Pixel>> matrice_Pixel;
    matrice_Pixel = image.convertTo2D();
    image.afficheMatrice(matrice_Pixel);
    //image.MatriceToImage(matrice_Pixel, height, width, maxColor, "output.ppm");

    // Test tracer de droite
    // std::vector<float> eqDroite;
    //eqDroite = image.equationDroite( 0, 0, 30, 30);
    //image.tracerDroite( eqDroite, matrice_Pixel );
    //image.MatriceToImage(matrice_Pixel, height, width, maxColor, "output.ppm");

    // Test tracer de droite aux coordonnées polaires
    vector<float> eqDroitePolaire;
    eqDroitePolaire = image.equationDroitePolaire(10, 30);
    // image.tracerDroitePolaire(eqDroitePolaire, matrice_Pixel);
    // image.MatriceToImage(matrice_Pixel, height, width, maxColor, "output.ppm");

    // Approche naive
    std::vector<std::tuple<double, double>> droites = image.getLignes(matrice_Pixel, 10, .3);

    affiche_tuples(droites);
    for (unsigned int i = 0; i<droites.size(); ++i)
        image.tracerSegment({float(get<0>(droites[i])), float(get<1>(droites[i]))}, matrice_Pixel);
    image.MatriceToImage(matrice_Pixel, "output.ppm");

}

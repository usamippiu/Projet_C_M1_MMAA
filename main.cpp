#include "image.h"
#include "pixel.h"
#include <iostream>
#include <fstream>
#include<tuple>
#include<cmath>

std::vector<std::vector<Pixel>> drawSinusoid(std::vector<std::vector<Pixel>>& input);
void affiche_tuples(std::vector<std::tuple<double, double>>& tuples);

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
    matrice_Pixel = image.convertTo2D();
    image.afficheMatrice(matrice_Pixel);
    //image.MatriceToImage(matrice_Pixel, height, width, maxColor, "output.ppm");

    // Test tracer de droite
   // std::vector<float> eqDroite;
    //eqDroite = image.equationDroite( 0, 0, 30, 30);
    //image.tracerDroite( eqDroite, matrice_Pixel );
    //image.MatriceToImage(matrice_Pixel, height, width, maxColor, "output.ppm");

    // Test tracer de droite aux coordonnées polaires
//    vector<float> eqDroitePolaire;
//    eqDroitePolaire = image.equationDroitePolaire( 10, 30 );
//    image.tracerDroitePolaire( eqDroitePolaire, matrice_Pixel );
//    image.MatriceToImage(matrice_Pixel, height, width, maxColor, "output.ppm");

    // Approche naive
    std::vector<std::tuple<double, double>> droites = image.getLignes(matrice_Pixel, 10, .3);

    affiche_tuples(droites);

    for (unsigned int i = 0; i<droites.size(); ++i)
        image.tracerDroitePolaire({float(get<0>(droites[i])), float(get<1>(droites[i]))}, matrice_Pixel);
    image.MatriceToImage(matrice_Pixel, "approche_naive.ppm");

    // Approche moins naive
    std::vector<std::vector<Pixel>> output = drawSinusoid(matrice_Pixel);
    image.MatriceToImage(output,"sinusoide.ppm");


}



// Trace une sinusoïde dans l'espace de Hough à partir des coordonnées d'un pixel
std::vector<std::vector<Pixel>> drawSinusoid(std::vector<std::vector<Pixel>>& input) {

    std::vector<std::vector<Pixel>> output(input.size(), std::vector<Pixel>(180, {0, 0, 0})); // on init une matrice de pixel de avec le même nombre de ligne que input
    //et 180 pixel par ligne car theta va jusqu'à 180 en radiants

    for (unsigned int x = 0; x < input.size(); x++) {
        for (unsigned int y = 0; y < input[0].size(); y++) {
            for (unsigned int theta = 0; theta < 180; theta++) {
                double rho = x * cos(theta * M_PI / 180) + y * sin(theta * M_PI / 180); // rho = equation de la sinusoide en fonction d'un point x,y du repère
                unsigned int rhoIndex = static_cast<unsigned int>(rho);

                if (rhoIndex >= 0 && rhoIndex < output.size()) {
                    // Incrémenter la matrice, = espace de Hough ?
                    output[rhoIndex][theta].r++;
                    output[rhoIndex][theta].g++;
                    output[rhoIndex][theta].b++;
                }
            }
        }
    }

    return output;
}

// Affichage tuples
void affiche_tuples(std::vector<std::tuple<double, double>>& tuples){
    std::cout << "------------------------" << std::endl;
    for (const auto& tuple : tuples) {
        std::cout << "(" << std::get<0>(tuple) << ", " << std::get<1>(tuple) << ")" << std::endl;
    }
}

#include "image.h"
#include "pixel.h"
#include <iostream>
#include <fstream>
#include<tuple>
#include<cmath>
#include<utility>

std::vector<std::vector<Pixel>> drawSinusoid(std::vector<std::vector<Pixel>>& input);
void affiche_tuples(std::vector<std::tuple<double, double>>& tuples);

using namespace std;
int main()
{

//    // Test de la classe image et ses méthodes
//    PPMImage image;
//    image.PPMImageLoader("m1projetcpp2.ppm");
//    // setters et getters
//    int width = image.getWidth();
//    int height = image.getHeight();
//    int maxColor = image.getMaxColor();
//    cout<< "width = " << width << endl;
//    cout<<"height =" << height << endl;
//    cout<<"maxColor =" << maxColor <<endl;
//
//    // Création de la matrice de pixel
//    std::vector<std::vector<Pixel>> matrice_Pixel;
//    matrice_Pixel = image.convertTo2D();
//    image.afficheMatrice(matrice_Pixel);
//    //image.MatriceToImage(matrice_Pixel, height, width, maxColor, "output.ppm");
//
//    // Test tracer de droite
//   // std::vector<float> eqDroite;
//    //eqDroite = image.equationDroite( 0, 0, 30, 30);
//    //image.tracerDroite( eqDroite, matrice_Pixel );
//    //image.MatriceToImage(matrice_Pixel, height, width, maxColor, "output.ppm");
//
//    // Test tracer de droite aux coordonnées polaires
////    vector<float> eqDroitePolaire;
////    eqDroitePolaire = image.equationDroitePolaire( 10, 30 );
////    image.tracerDroitePolaire( eqDroitePolaire, matrice_Pixel );
////    image.MatriceToImage(matrice_Pixel, height, width, maxColor, "output.ppm");
//
//    // Approche naive
//    std::vector<std::tuple<double, double>> droites = image.getLignes(matrice_Pixel, 10, .3);
//
//    affiche_tuples(droites);
//
//    for (unsigned int i = 0; i<droites.size(); ++i)
//        image.tracerDroitePolaire({float(get<0>(droites[i])), float(get<1>(droites[i]))}, matrice_Pixel);
//    image.MatriceToImage(matrice_Pixel, "approche_naive.ppm");
//
//    // Approche moins naive
//    std::vector<std::vector<Pixel>> output = drawSinusoid(matrice_Pixel);
//    //image.MatriceToImage(output, "sinusoide.ppm");
//    image.afficheMatrice(output);

    // Tests :
    // Test de la classe image et ses méthodes
    PPMImage image;
    image.PPMImageLoader("test.ppm");
    vector<vector<Pixel>> matrice_Pixel_test;
    matrice_Pixel_test = image.convertTo2D();
    image.afficheMatrice(matrice_Pixel_test);

    vector<vector<Pixel>> output = drawSinusoid(matrice_Pixel_test);
    image.MatriceToImage(output, "sinusoide.ppm");
    image.afficheMatrice(output);

    std::pair<int, int> coordonnees_max = image.getMaximum(output);
    cout << "coordonnées maximum = (" << coordonnees_max.first << " , " << coordonnees_max.second << ")" << endl;
    //std::vector<float> coeff = image.equationDroitePolaire(float x, float y, float rho, float theta);
    //cout <<" a = " << coeff[0] << "b = " << coeff[1] << endl;
//    void tracerDroitePolaire(std::vector<float> eqDroite, std::vector<std::vector<Pixel>>& input);
}



// Trace une sinusoïde dans l'espace de Hough à partir des coordonnées d'un pixel
std::vector<std::vector<Pixel>> drawSinusoid(std::vector<std::vector<Pixel>>& input) {

    std::vector<std::vector<Pixel>> output(180, std::vector<Pixel>(3*input.size(), {0, 0, 0})); // matrice de pixel dans le repère theta,rho
    //et 180 pixel par ligne car theta va jusqu'à 180 en radiants

    for (unsigned int x = 1; x < input.size(); x++) {
        for (unsigned int y = 1; y < input[0].size(); y++) {
            for (unsigned int theta = 0; theta < 180; theta++) {
                // sinusoide dans le repere theta,rho equivalente au point x,j dans l'image
                double rho = x * cos(theta * M_PI/180 ) + y * sin(theta * M_PI/180 );
                //cout << rho << endl;
                int rhoIndex = (int) round(3*rho);

                if (rhoIndex >= 0 && rhoIndex < output[0].size()) {
                    // Incrémenter la matrice, = espace de Hough ?
                    output[theta][rhoIndex].r++;
                    output[theta][rhoIndex].g++;
                    output[theta][rhoIndex].b++;
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


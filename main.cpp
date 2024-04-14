#include "image.h"
#include "pixel.h"
#include <iostream>
#include <fstream>
#include<tuple>
#include<cmath>
#include<utility>

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
    //image.MatriceToImage(matrice_Pixel, "output.ppm");

    // Approche naive
    std::vector<std::tuple<double, double>> droites = image.getLignesNaif(matrice_Pixel, 10, .3);

    affiche_tuples(droites);

    for (unsigned int i = 0; i<droites.size(); ++i)
        image.tracerDroite({float(get<0>(droites[i])), float(get<1>(droites[i]))}, matrice_Pixel);
    image.MatriceToImage(matrice_Pixel, "approche_naive.ppm");
    cout << "\n Fichier -approche_naive.ppm crée" << endl;


    // Méthode moins naïve
    droites = image.getLignesNonNaif(matrice_Pixel, 10, .3);

    affiche_tuples(droites);

    for (unsigned int i = 0; i<droites.size(); ++i)
        image.tracerDroite({float(get<0>(droites[i])), float(get<1>(droites[i]))}, matrice_Pixel);
    image.MatriceToImage(matrice_Pixel, "approche_moins_naive.ppm");
    cout << "\n Fichier -approche_moins_naive.ppm crée" << endl;


}

// Affichage tuples
void affiche_tuples(std::vector<std::tuple<double, double>>& tuples){
    cout << "------------------------" << endl;
    cout << "Coefficients des droites = " << endl;
    for (const auto& tuple : tuples) {
        cout << "(" << get<0>(tuple) << ", " << get<1>(tuple) << ")" << endl;
    }
}


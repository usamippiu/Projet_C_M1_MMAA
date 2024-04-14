#ifndef _IMAGE_H_
#define _IMAGE_H_
#include "pixel.h"
#include <vector>
#include <string>

// image ppm = valeurs ligne par ligne
// indice i =0 = en haut à gauche de l'image etc
class PPMImage {
private:
    unsigned int width, height, maxColor;

public:
    std::vector<Pixel> pixels; // Vecteur de pixels qui represente l'image ppm
    void PPMImageLoader(const std::string& filename);
    int getWidth() const;
    int getHeight() const;
    int getMaxColor() const;
    std::vector<std::vector<Pixel>> convertTo2D(); // Convertit le vecteur de pixel en matrice
    void MatriceToImage(std::vector<std::vector<Pixel>>& input, std::string filename); // Convertit une matrice de pixel en image
    void afficheMatrice(std::vector<std::vector<Pixel>>& input); // Non utilisé
    std::vector<float> equationDroite(float x1, float y1, float x2, float y2);
    void tracerDroite(std::vector<float> eqDroite, std::vector<std::vector<Pixel>>& input); // Trace une droite sur l'image
    std::vector<float> coordonneesPolaires(float x, float y); // Non utilisé
    std::vector<float> equationDroitePolaire(float x, float y); // Non utilisé
    std::vector<std::tuple<double, double>> getNotWhite(std::vector<std::vector<Pixel>>& input); // Recupère les pixels non blancs
    std::vector<std::tuple<double, double>> getLignesNaif(std::vector<std::vector<Pixel>>& input, int nb_intersections, double threshold); // Méthode naive
    std::vector<std::tuple<double, double>> getLignesNonNaif(std::vector<std::vector<Pixel>>& input, int nb_intersections, double threshold); // Méthode non naive

};

#endif

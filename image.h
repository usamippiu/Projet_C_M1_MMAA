#ifndef _IMAGE_H_
#define _IMAGE_H_
#include "pixel.h"
#include <vector>
#include <string>
#include <utility>

// image ppm = valeurs ligne par ligne
// indice i =0 = en haut à gauche de l'image etc
class PPMImage {
private:
    unsigned int width, height, maxColor;

public:
    std::vector<Pixel> pixels; // Attribut matrice de pixel
    void PPMImageLoader(const std::string& filename); // Charger et initialiser l'image
    // Getters
    int getWidth() const;
    int getHeight() const;
    int getMaxColor() const;

    // Affichage et conversion matrice - image
    void afficheMatrice(std::vector<std::vector<Pixel>>& input);
    std::vector<std::vector<Pixel>> convertTo2D();
    void MatriceToImage(std::vector<std::vector<Pixel>>& input, std::string filename);

    // Tracer de droite et traitement pour espace de Hough
    std::vector<float> equationDroite(float x1, float y1, float x2, float y2);
    void tracerDroite(std::vector<float> eqDroite, std::vector<std::vector<Pixel>>& input);
    std::vector<float> coordonneesPolaires(float x, float y);
    std::vector<float> equationDroitePolaire(float x, float y);
    void tracerDroitePolaire(std::vector<float> eqDroite, std::vector<std::vector<Pixel>>& input);
    void tracerSegment(std::vector<float> eqDroite, std::vector<std::vector<Pixel>>& input);
    std::vector<std::tuple<double, double>> getNotWhite(std::vector<std::vector<Pixel>>& input);
    std::vector<std::tuple<double, double>> getLignes(std::vector<std::vector<Pixel>>& input, int nb_intersections, double threshold);
    std::pair<int, int> maximum(const std::vector<std::vector<Pixel>>& input); // Avoir les coordonnées du maximum de la matrice de pixel

};



#endif

#include "image.h"
#include "pixel.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include<cmath>
#include<tuple>

// Charger une image
void PPMImage::PPMImageLoader(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    unsigned int lineCount = 0;

    // iteration sur les lignes
    while (std::getline(file, line)) {
        if (line[0] == '#')
            continue;

        std::istringstream iss(line);

        // Dans les ppm la taille de l'image se trouve en ligne 1
        if (lineCount == 1){
            iss >> width >> height;
            this->width = width;
            this->height = height;
            this->pixels.resize(width * height);
        }
        if (lineCount == 2){
            iss >> maxColor;
            this->maxColor = maxColor;
        }

        // Si on arrive à la troisième ligne alors on a les couleurs de nos pixel qu'on stock
        if (lineCount >= 3){
            for (unsigned i = 0; i < width*height; ++i) {
                this->pixels[i].r = std::stoi(line);
                std::getline(file, line);
                this->pixels[i].g = std::stoi(line);
                std::getline(file, line);
                this->pixels[i].b = std::stoi(line);
                std::getline(file, line);
            }

            break;
        }

        lineCount++;
    }

    file.close();
}

// Avoir la taille de l'image :
int PPMImage::getWidth() const {
    return this->width;
}

int PPMImage::getHeight() const {
    return this->height;
}

int PPMImage::getMaxColor() const{
    return this->maxColor;
}

// Afficher la matrice de Pixel
void PPMImage::afficheMatrice(std::vector<std::vector<Pixel>>&  input) {
    for(unsigned int i = 0; i < this->height; i++ )
    {
        for(unsigned int j = 0; j < this->width ; j++)
        {
            std::cout << "r " << input[i][j].getPixel()[0] << " g " << input[i][j].getPixel()[1] << " b " << input[i][j].getPixel()[2] << std::endl;
        }
    }
}

// Conversion pixel vecteur ligne en matrice
std::vector<std::vector<Pixel>> PPMImage::convertTo2D() {
    std::vector<std::vector<Pixel>> output(this->height, std::vector<Pixel>(this->width));

    for (unsigned  i = 0; i < this->height; ++i) {
        for (unsigned int j = 0; j < this->width; ++j) {
            output[i][j] = this->pixels[i * width + j];
        }
    }

    return output;
}

//Conversion matrice en image
void PPMImage::MatriceToImage(std::vector<std::vector<Pixel>>& input, std::string filename){
    std::ofstream fichier;
    fichier.open(filename);

    fichier << "P3" <<std::endl;
    fichier << "# resolution " <<std::endl;
    fichier << this->width << " "<< this->height <<std::endl;
    fichier << "# avec 255 comme val max" <<std::endl;
    fichier << this->maxColor <<std::endl;
    fichier << "# debut de l image" <<std::endl;

    for(unsigned int i = 0; i < this->height; i++ )
    {
        for(unsigned int j = 0; j < this->width ; j++)
        {
            fichier << input[i][j].getPixel()[0] <<std::endl;
            fichier << input[i][j].getPixel()[1] <<std::endl;
            fichier << input[i][j].getPixel()[2] <<std::endl;
        }
    }
    fichier.close();
}

// Maillage de l'image
// discrétiser l'espace de paramètres, à le découper en petits rectangles, et à dénombrer pour chaque rectangle le nombre de courbe y passant.
// On construit ainsi une matrice dite d'accumulation, les maxima locaux de cette matrice correspondant à des droites probables.

std::vector<float> PPMImage::equationDroite( float x1, float y1, float x2, float y2 ){
    float a = (y2 - y1) / (x2 - x1);
    float b = y1 - a * x1;
    return {a, b};
}

void PPMImage::tracerDroite( std::vector<float> eqDroite, std::vector<std::vector<Pixel>>& input )
{
    // si la droite n'est pas verticale

    if ( std::abs(eqDroite[0]) < 1 ){
        for(unsigned int i = 0; i < height ; ++i)
        {
            float y = eqDroite[0] * i + eqDroite[1]; //equation de droite pour le nouveau point
            unsigned int y_entier = (unsigned int) std::round(y);
            if ( y_entier <= height)
            {
                input[i][y_entier].setRGB( 0, 0, 0 );
            }
        }
    }

    // sinon

    else {
        for(unsigned int i = 0; i < width ; ++i)
        {
            float y = eqDroite[0] * i + eqDroite[1]; //equation de droite pour le nouveau point
            unsigned int y_entier = (unsigned int) std::round(y);
            if ( y_entier <= width)
            {
                input[y_entier][i].setRGB( 0, 0, 0 );
            }
        }
    }

}

// Conversion coordonnées polaires
std::vector<float> PPMImage::coordonneesPolaires(float x, float y) {
    float rho = std::sqrt(x * x + y * y);
    float theta = std::atan2(y, x);
    return {std::cos(theta), std::sin(theta), rho, theta};
}

// y = - costh/sinth * x + rho/ sinth
// theta = angle entre la droite et l'axe des abscisses
// rho = distance entre la droite et l'origine = matrice_pixel[0][0]
// rho = x costh + y sinth
std::vector<float> PPMImage::equationDroitePolaire( float x, float y )
{
    float cosTheta = coordonneesPolaires( x, y)[0];
    float sinTheta = coordonneesPolaires( x, y)[1];
    // rho pour le point
    float rho = coordonneesPolaires( x, y)[2];
    // a et b de l'équation de la droite
    float a = -cosTheta / sinTheta;
    float b = rho / sinTheta;

    return {a, b};
}

// Droite polaire
void PPMImage::tracerDroitePolaire( std::vector<float> eqDroite, std::vector<std::vector<Pixel>>& input )
{
    for (unsigned int i = 0; i < height; i++)
    {
        float y = eqDroite[0] * i + eqDroite[1]; //equation de droite pour le nouveau point
        unsigned int y_entier = (unsigned int) std::round(y);

        if ( y_entier < width )
        {
            input[i][y_entier].setRGB( 0, 0, 0 );
        }
    }
}

// Traitement pour droites dans l'espace de Hough
std::vector<std::tuple<double, double>> PPMImage::getNotWhite( std::vector<std::vector<Pixel>>& input )
{
    std::vector<std::tuple<double, double>> notWhite;
     for (unsigned int i = 0; i < height; i++)
     {
         for (unsigned int j = 0; j < width; j++)
         {
            if (input[i][j].getPixel()[0] != 255 || input[i][j].getPixel()[1] != 255  || input[i][j].getPixel()[2] != 255 ){
                notWhite.push_back( std::make_tuple(i,j) );
            }
         }
     }
     return notWhite;
}

double tuple_norm(const std::tuple<double, double>& a, const std::tuple<double, double>& b) {
    double dx = std::get<0>(b) - std::get<0>(a);
    double dy = std::get<1>(b) - std::get<1>(a);
    return std::sqrt(dx * dx + dy * dy);
}

void remove_close_tuples(std::vector<std::tuple<double, double>>& vec, double threshold) {
    auto it = vec.begin();
    while (it != vec.end()) {
        bool removed = false;
        auto it2 = std::next(it);
        while (it2 != vec.end()) {
            if (tuple_norm(*it, *it2) < threshold) {
                it2 = vec.erase(it2);
                removed = true;
            } else {
                ++it2;
            }
        }
        if (!removed) ++it;
    }
}

std::vector<std::tuple<double, double>> diviserTuple(const std::vector<std::tuple<double, double>>& vecteur, double quotient) {

    std::vector<std::tuple<double, double>> resultat;

    for (const auto& element : vecteur) {
        double premier = std::get<0>(element) / quotient;
        double deuxieme = std::get<1>(element) / quotient;

        resultat.push_back(std::make_tuple(premier, deuxieme));
    }

    return resultat;
}

std::vector<std::tuple<double, double>> multiplierTuple(const std::vector<std::tuple<double, double>>& vecteur, double quotient) {

    std::vector<std::tuple<double, double>> resultat;

    for (const auto& element : vecteur) {
        double premier = std::get<0>(element);
        double deuxieme = std::get<1>(element) * quotient;

        resultat.push_back(std::make_tuple(premier, deuxieme));
    }

    return resultat;
}

std::vector<std::tuple<double, double>> PPMImage::getLignes(std::vector<std::vector<Pixel>>& matrice_Pixel, int nb_intersections, double threshold){
    std::vector<std::tuple<double, double>> notWhite;
    notWhite = this->getNotWhite(matrice_Pixel);

    std::vector<std::tuple<double, double>> scaledTuples = diviserTuple(notWhite, 30.);
    std::vector<std::tuple<double, double>> droites;

    float x_min = -2;
    float x_max = 2;
    float y_min = -2;
    float y_max = 2;

    float precision = .001;

    int n_cols = std::round(std::abs(x_min-x_max)/precision);
    int n_rows = std::round(std::abs(y_min-y_max)/precision);

    std::vector<std::vector<int>> hough(n_rows, std::vector<int>(n_cols, 0));

    for (const std::tuple<double, double>& tuple : scaledTuples) {
        double x = std::get<0>(tuple);
        double y = std::get<1>(tuple);
        for(double m = 0; m < n_cols ; ++m){
            double b = y - (m*std::abs(x_min-x_max)/n_cols+x_min)*x;
            double b_round = std::round(b/precision) - y_min/precision;
            if (b_round < n_rows){
                hough[b_round][m] +=1;
            }
        }
    }
    for (int i = 0; i < n_rows ; ++i){
        for(int j = 0; j < n_cols ; ++j){
            if (hough[i][j] >= nb_intersections)
            droites.push_back(std::make_tuple(j*precision+x_min, i*precision+y_min));
        }
    }

    remove_close_tuples(droites, threshold);

    std::vector<std::tuple<double, double>> rescaledDroites = multiplierTuple(droites, 30.);

    return rescaledDroites;
}

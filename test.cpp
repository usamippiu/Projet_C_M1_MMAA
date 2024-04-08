#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main() {
    ifstream file("m1projetcpp2.ppm");
    vector<int> dimensions;

    if (!file.is_open()) {
        cerr << "Erreur: Ouverture du fichier m1projetcpp2.ppm" << endl;
        return 1;
    }

    string magic;
    file >> magic;
    if (magic != "P3") {
        cerr << "Erreur: Format du fichier" << endl;
        file.close();
        return 1;
    }

    int lineCount = 0;
    for (string ligne; getline(file, ligne); ) {
        stringstream fluxLigne(ligne);

        for (string mot; getline(fluxLigne, mot, ' '); ) {
            //int composante = stoi(mot);
            //dimensions.push_back(composante);
            cout << mot << endl;

        }
        lineCount += 1;


    }

//    // Affichage
//    for (int dimension : dimensions) {
//        cout << dimension << " ";
//    }
//    cout << endl;

    file.close();

    return 0;
}

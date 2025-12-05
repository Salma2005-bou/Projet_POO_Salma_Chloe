#pragma once
#include <iostream>
using namespace std;

#include "Afficheur.h"
#include "Grille.h"

class AfficheurConsole : public Afficheur {
public:

    void afficher(Grille* grille, int nbIterations = -1) override {

        int iteration = 0;

        while (nbIterations == -1 || iteration < nbIterations) {

            cout << "" << endl;
            cout << "Iteration : " << iteration << endl;

            for (int i = 0; i < grille->getHauteur(); ++i) {
                for (int j = 0; j < grille->getLargeur(); ++j) {
                    cout << (grille->getCellule(i,j)->estVivante() ? "O " : ". ");
                }
                cout << endl;
            }

            grille->calculerGenerationSuivante();
            grille->appliquerGenerationSuivante();

            iteration++;
        }
    }

    ~AfficheurConsole() override {}
};

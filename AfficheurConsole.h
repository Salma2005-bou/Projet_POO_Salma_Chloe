#pragma once
#include <iostream>
using namespace std;

#include "Afficheur.h"
#include "Grille.h"

class AfficheurConsole : public Afficheur {
    public:
        void afficher ( Grille *grille ) override {
            for (int i = 0; i < grille->getHauteur(); ++i) {
                for (int j = 0; j < grille->getLargeur(); ++j) {
                    if (grille -> getCellule(i,j) -> estVivante()) {
                        std::cout << "O ";
                    } else {
                        std::cout << ". ";
                    }
                }
                std::cout << std::endl;
            }
        }
        ~AfficheurConsole() override {}
};

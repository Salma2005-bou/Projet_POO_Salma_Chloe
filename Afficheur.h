#pragma once
#include <iostream>
using namespace std;

class Grille;

class Afficheur {
    public:
        virtual void afficher ( Grille *grille ) = 0;
        virtual ~Afficheur() {}
};

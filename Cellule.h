#pragma once
#include <iostream>
using namespace std;
#include "EtatCellule.h"

class Cellule {
private:
    int x;
    int y;
    EtatCellule* etat; 
    EtatCellule* etatSuivant;
public:
    Cellule(int x, int y, EtatCellule* etatInitial) : x(x), y(y), etat(etatInitial), etatSuivant(nullptr) {} 
    
    ~Cellule() {
        delete etat;
        delete etatSuivant;  
    }

    bool estVivante() {
        return etat -> estVivante();
    }

    void setEtatSuivant(EtatCellule* x){ 
        etatSuivant = x;
    }

    void appliquerEtatSuivant(){ 
        delete etat;
        etat = etatSuivant;
        etatSuivant = nullptr;
    }

    EtatCellule* getEtat() { 
        return this -> etat;
    }

    void setEtat(EtatCellule* nouvelEtat){ 
        etat = nouvelEtat;
    }
};

#pragma once
#include <iostream>
using namespace std;

class EtatCellule ;

class Cellule {
private:
    int x;
    int y;
    EtatCellule* etat; // vivant ou mort
    EtatCellule* etatSuivant; // futur état
public:
    Cellule(int x, int y, EtatCellule* etatInitial) : x(x), y(y), etat(etatInitial), etatSuivant(nullptr) {} // crée une cellule à un point donné avec un état 1 ou 0
    
    bool estVivante() {
        return etat -> estVivante();
    }

    void setEtatSuivant(EtatCellule* x){ // définit le futur état de la cellule
        etatSuivant = x;
    }

    void appliquerEtatSuivant(){ // remplace etat par etatSuivant
        etat = etatSuivant;
        etatSuivant = nullptr;
    }

    EtatCellule* getEtat() { // objet qui représente l'état actuel
        return this -> etat;
    }

    void setEtat(EtatCellule* nouvelEtat){ // change l'état de la cellule
        etat = nouvelEtat;
    }
};

class EtatCellule {
public:
    virtual bool estVivante() = 0 ;
};

class EtatVivant : public EtatCellule {
public:
    bool estVivante() override {
        return true;
    }
};

class EtatMort : public EtatCellule {
public:
    bool estVivante() override {
        return false;
    }
};
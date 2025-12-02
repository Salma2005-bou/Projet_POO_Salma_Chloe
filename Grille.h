#pragma once
#include <vector>
#include <iostream>
using namespace std;

#include "Cellule.h"

class Grille {
private:
    vector<vector<Cellule*>> cellules; // représente l'ensemble des ccellules de la grille
    int largeur;
    int hauteur;
public:
    Grille (int l, int h) : largeur(l), hauteur(h) {} // constrcteur
    
    int getLargeur(){
        this -> largeur = largeur;
        return largeur;
    }

    int getHauteur() {
        this -> hauteur = hauteur;
        return hauteur;
    }

    Cellule getCellule(int x, int y) { // retourne la cellule aux coordonnées x et y 
        
    }

    void initialiserDepuisMatrice (vector<vector<bool>>matrice) { //Remplit la grille à partir du fichier d'entrée

    }

    virtual int compterVoisinsVivants(int x, int y) = 0 ; // retourne le nombre de voisins vivants autour d'une cellule
    virtual void calculerGenerationSuivante() = 0 ; // parcourt la grille et calcule pour chaque cellules, leur prochain état (stocker dans etatSuivant)
    
    void appliquerGenerationSuivante() {

    }
};

class GrilleNormale : public Grille {
public:
    int compterVoisinsVivants(int x, int y) override { 

    }

    void calculerGenerationSuivante() override { 
    }
};

class GrilleTorique : public Grille {
public :
    int compterVoisinsVivants(int x, int y) override {

    }

    void calculerGenerationSuivante() override {

    }
};
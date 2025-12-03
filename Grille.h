#pragma once
#include <map>
#include <vector>
#include <iostream>
using namespace std;

#include "Cellule.h"
#include "Regle.h"
#include "EtatVivant.h"
#include "EtatMort.h"

class Grille {
private:
    vector<vector<Cellule*>> cellules; // représente l'ensemble des ccellules de la grille
    Regle* regle;
    int largeur;
    int hauteur;
public:
    Grille (int l, int h, Regle* r) : largeur(l), hauteur(h), regle(r) {
    cellules = vector<vector<Cellule*>> // création de la matrice de taille hauteur (lignes) x largeur (colonnes)
              (hauteur, // matrice avec "hauteur" nbr de lignes
              vector<Cellule*> (largeur, nullptr)); // largeur = le nombre de colonnes, contenant la valeur NULL
    }
    
    ~Grille() {
        for (int i = 0; i < hauteur; i++){
            for (int j = 0; j < largeur; j++){
                delete cellules[i][j];
            }
        }
        delete regle;        
    }

    int getLargeur(){
        return this -> largeur;
    }

    int getHauteur() {
        return this -> hauteur;
    }

    Cellule* getCellule(int i, int j) { // retourne la cellule aux coordonnées x et y 
        return this -> cellules[i][j];
    }

    Regle* getRegle(){
        return this -> regle;
    }

    void initialiserDepuisMatrice (vector<vector<bool>> matrice) { //Remplit la grille à partir du fichier d'entrée
       
        for (int i = 0; i < hauteur ; i++) {
            for (int j = 0; j < largeur; j++) {

                // matrice initiale donnée dans le fichier 
                bool etatDeLaCellule = matrice[i][j];

                if (etatDeLaCellule){
                    cellules[i][j] = new Cellule( j, i, new EtatVivant());
                }
            
                else {
                    cellules[i][j] = new Cellule( j, i, new EtatMort());
                }
            }
        }
    }

    virtual int compterVoisinsVivants(int x, int y) = 0 ; // retourne le nombre de voisins vivants autour d'une cellule
    virtual void calculerGenerationSuivante() = 0 ; // parcourt la grille et calcule pour chaque cellules, leur prochain état (stocker dans etatSuivant)

    void appliquerGenerationSuivante() {
        for (int i = 0 ; i < getHauteur() ; i++){
            for (int j = 0 ; j < getLargeur() ; j++){
                getCellule(i, j) -> appliquerEtatSuivant();
            }
        }
    }
};

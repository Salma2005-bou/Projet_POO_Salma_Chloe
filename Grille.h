#pragma once
#include <map>
#include <vector>
#include <iostream>
using namespace std;

#include "Cellule.h"
#include "Regle.h"

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

    virtual int compterVoisinsVivants(int x, int y); // retourne le nombre de voisins vivants autour d'une cellule
    virtual void calculerGenerationSuivante(); // parcourt la grille et calcule pour chaque cellules, leur prochain état (stocker dans etatSuivant)

    void appliquerGenerationSuivante() {
        for (int i = 0 ; i < getHauteur() ; i++){
            for (int j = 0 ; j < getLargeur() ; j++){
                getCellule(i, j) -> appliquerEtatSuivant();
            }
        }
    }
};

class GrilleNormale : public Grille {
public:

    GrilleNormale(int l, int h, Regle* r) : Grille(l, h, r) {}

    int compterVoisinsVivants(int i, int j) override { 

        map <Cellule*, bool> Voisins ;

        // insertion dans la liste, de l'ensemble des voisins à une cellule donnée

        // Les 3 cases du haut
        if (i-1 >= 0 && j-1 >= 0) {
            Voisins.insert({getCellule(i-1,j-1), getCellule(i-1, j-1) -> estVivante() });}
        if (i-1 >= 0) {
            Voisins.insert({getCellule(i-1,j), getCellule(i-1, j) -> estVivante() });}
        if (i-1 >=0 && j+1 < getLargeur()) {
            Voisins.insert({getCellule(i-1,j+1), getCellule(i-1, j+1) -> estVivante() });}


        // Les 2 cases des côtés
        if (j-1 >= 0) {
            Voisins.insert({getCellule(i,j-1), getCellule(i, j-1) -> estVivante() });}
        if (j+1 < getLargeur()){
            Voisins.insert({getCellule(i,j+1), getCellule(i, j+1) -> estVivante() });}

        // Les 3 cases d'en dessous
        if (i+1 < getHauteur() && j-1 >= 0) {
            Voisins.insert({getCellule(i+1,j-1), getCellule(i+1, j-1) -> estVivante() });}
        if (i+1 < getHauteur()) {
            Voisins.insert({getCellule(i+1,j), getCellule(i+1, j) -> estVivante() });}
        if (i+1 < getHauteur() && j+1 < getLargeur()) {
            Voisins.insert({getCellule(i+1,j+1), getCellule(i+1, j+1) -> estVivante() });}

        // Recherche du nombre de voisins vivants
        int cpt = 0;

        for (auto& l : Voisins) {
            if (l.second){
                cpt++;
            }
           
            return cpt;
        }
    }

    void calculerGenerationSuivante() override { 
        for (int i = 0; i < getHauteur(); i++){
            for (int j = 0; j < getLargeur(); j++){

                int nb_voisin = compterVoisinsVivants(i, j);
                EtatCellule* etatFutur = getRegle() -> devraitEtreAppliquee(getCellule(i, j) -> getEtat(), nb_voisin);

                Cellule* cellule = getCellule(i,j);
                cellule -> setEtatSuivant(etatFutur);
            }
        }
    }
};


/*
class GrilleTorique : public Grille {
public :
    int compterVoisinsVivants(int x, int y) override {

    }

    void calculerGenerationSuivante() override {

    }
};
*/
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
    vector<vector<Cellule*>> cellules; 
    Regle* regle;             // La grille n'est PAS propriétaire de la règle !
    int largeur;
    int hauteur;

public:
    Grille(int l, int h, Regle* r) 
        : largeur(l), hauteur(h), regle(r)
    {
        // Création de la matrice hauteur x largeur remplie de nullptr
        cellules = vector<vector<Cellule*>>(
            hauteur,
            vector<Cellule*>(largeur, nullptr)
        );
    }

    virtual ~Grille() {
        // Libérer toutes les cellules créées
        for (int i = 0; i < hauteur; i++) {
            for (int j = 0; j < largeur; j++) {
                delete cellules[i][j];
            }
        }

        
    }

    int getLargeur() const { return largeur; }
    int getHauteur() const { return hauteur; }

    Cellule* getCellule(int i, int j) const {
        return cellules[i][j];   // peut être nullptr si non initialisé
    }

    Regle* getRegle() const { return regle; }

    // Initialise la grille à partir de la matrice du fichier
    void initialiserDepuisMatrice(const vector<vector<bool>>& matrice) {
        for (int i = 0; i < hauteur; i++) {
            for (int j = 0; j < largeur; j++) {

                // Supprimer l'ancienne cellule si elle existe
                if (cellules[i][j] != nullptr)
                    delete cellules[i][j];

                if (matrice[i][j]) 
                    cellules[i][j] = new Cellule(j, i, new EtatVivant());
                else
                    cellules[i][j] = new Cellule(j, i, new EtatMort());
            }
        }
    }

    // Méthodes abstraites
    virtual int compterVoisinsVivants(int x, int y) = 0;
    virtual void calculerGenerationSuivante() = 0;

    // Applique l'étatSuivant après avoir calculé la génération suivante
    void appliquerGenerationSuivante() {
        for (int i = 0; i < hauteur; i++) {
            for (int j = 0; j < largeur; j++) {
                cellules[i][j]->appliquerEtatSuivant();
            }
        }
    }
};

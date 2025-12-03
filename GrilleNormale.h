#pragma once
#include "Grille.h"

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
        }
        return cpt;
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

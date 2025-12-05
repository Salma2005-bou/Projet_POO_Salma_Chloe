#pragma once
#include "Grille.h"

class GrilleNormale : public Grille {
public:

    GrilleNormale(int l, int h, Regle* r)
        : Grille(l, h, r) {}

    // --- Compte les voisins vivants ---
    int compterVoisinsVivants(int i, int j) override {

        static const int dx[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
        static const int dy[8] = {-1, 0, 1,-1, 1,-1, 0, 1};

        int cpt = 0;

        for (int k = 0; k < 8; k++) {
            int ni = i + dx[k];
            int nj = j + dy[k];

            if (ni >= 0 && ni < getHauteur() &&
                nj >= 0 && nj < getLargeur()) {

                Cellule* c = getCellule(ni, nj);
                if (c && c->estVivante())
                    cpt++;
            }
        }

        return cpt;
    }

    // --- Calcul de la génération suivante ---
    void calculerGenerationSuivante() override {

        for (int i = 0; i < getHauteur(); i++) {
            for (int j = 0; j < getLargeur(); j++) {

                Cellule* cellule = getCellule(i, j);

                if (!cellule) continue;

                int nb_voisins = compterVoisinsVivants(i, j);

                EtatCellule* futur =
                    getRegle()->devraitEtreAppliquee(cellule->getEtat(), nb_voisins);

                cellule->setEtatSuivant(futur);
            }
        }
    }
};

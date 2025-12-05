#pragma once
#include "Regle.h"

class RegleConway : public Regle {
public:
    EtatCellule* devraitEtreAppliquee(EtatCellule* etatActuel,int voisinsVivants) override {//  règles de Conway
        // Une cellule vivante avec moins de 2 ou plus de 3 voisins vivants meurt
        // La cellule est actuellement vivante
        if (etatActuel -> estVivante()) {
        // La cellule meurt si <2 et >3 voisins vivants
        if (voisinsVivants < 2 || voisinsVivants > 3) {
            return new EtatMort(); 
        } 
        else {
            return new EtatVivant() ;  //La cellule reste vivant
        }
    } 
    else {
        //La cellule est actuellement morte
        if (voisinsVivants == 3){ // vivante si exactement 3 voisins
            return new EtatVivant();
        }

        else {
            return new EtatMort();
        }
     
    }
}
};

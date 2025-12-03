#include "Cellule.h"

class Regle {
public:
    virtual EtatCellule* devraitEtreAppliquee(EtatCellule* etatActuel,int voisinsVivants)  = 0;
    virtual ~Regle() {}
};

class RegleConway : public Regle {
public:
    EtatCellule* devraitEtreAppliquee(EtatCellule* etatActuel,int voisinsVivants) override {
    if (etatActuel -> estVivante()) {
        if (voisinsVivants < 2 || voisinsVivants > 3) {
            return new EtatMort(); 
        } 
        
        else {
            return new EtatVivant() ;  
        }
    } 
    else {
        if (voisinsVivants == 3){ // vivante si exactement 3 voisins
            return new EtatVivant();
        }

        else {
            return new EtatMort();
        }
     
    }
}
};
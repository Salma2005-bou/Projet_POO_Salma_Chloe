#pragma once
#include "Cellule.h"
#include "EtatCellule.h"
#include "EtatVivant.h"
#include "EtatMort.h"

class Regle {
public:
    virtual EtatCellule* devraitEtreAppliquee(EtatCellule* etatActuel,int voisinsVivants)  = 0;
    virtual ~Regle() {}
};

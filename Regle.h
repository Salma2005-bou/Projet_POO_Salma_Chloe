#pragma once
#include "Cellule.h"
#include "EtatCellule.h"
#include "EtatVivant.h"
#include "EtatMort.h"

class Regle {
public:
    // Détermine le prochain état d'une cellule (vivante/morte) selon ses voisins.
    // Chaque règle du jeu doit fournir sa propre implémentation de cette méthode
    virtual EtatCellule* devraitEtreAppliquee(EtatCellule* etatActuel,int voisinsVivants)  = 0;
    virtual ~Regle() {} // Destructeur virtuel pour éviter les fuites mémoire
};

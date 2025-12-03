#include "Grille.h"
#include "Regle.h"
#include "Afficheur.h"

class JeuDeLaVie {
    private:
        Grille* grille; 
        Regle* regle;
        Afficheur* afficheur;
        int nombreTterations;
    public:
        // Constructeur pour initialiser la grille, la règle et l'afficheur
        JeuDeLaVie(Grille* g, Regle* r, Afficheur* a) : grille(g), regle(r), afficheur(a) {}
        
    }
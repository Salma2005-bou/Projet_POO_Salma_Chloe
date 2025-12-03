#include <iostream>
#include <vector>

#include "GrilleNormale.h"
#include "RegleConway.h"
#include "Afficheur.h"
#include "AfficheurConsole.h"
#include "AfficheurGraphique.h"
#include "JeuDeLaVie.h"
#include "EtatVivant.h"
#include "EtatMort.h"

using namespace std;

int main() {


    string nomFichier;
    cout << "Nom du fichier contenant la grille : ";
    cin >> nomFichier;

    

    int choixMode;
    cout << "Choisissez le mode d'affichage :" << endl;
    cout << "1. Console" << endl;
    cout << "2. Graphique (SFML)" << endl;
    cout << "Votre choix : ";
    cin >> choixMode;

    // 1. Lire matrice depuis fichier
    vector<vector<bool>> matrice;
    Fichier f;

    if (!f.lireMatrice(nomFichier, matrice)) {
        cout << "Erreur fichier" << endl;
        return 1;
    }

    // 2. Déduire dimensions
    int hauteur = matrice.size();
    int largeur = matrice[0].size();
    
    Regle* regle = new RegleConway();
    GrilleNormale* grille = new GrilleNormale(largeur, hauteur, regle);

    // Afficheur choisi par l'utilisateur
    Afficheur* afficheur = nullptr;

    if (choixMode == 1) {
        afficheur = new AfficheurConsole();
    } 
    else if (choixMode == 2) {
        afficheur = new AfficheurGraphique();
    } 
    else {
        cout << "Choix invalide." << endl;
        delete grille;
        return 1;
    }

    // Création du JeuDeLaVie
    JeuDeLaVie jeu(grille, regle, afficheur); 

    jeu.initialiserGrilleDepuisFichier(nomFichier);

    if (choixMode == 1) {
        int iterations;
        cout << "Nombre d'iterations : ";
        cin >> iterations;

        jeu.executer(iterations);
    }
    else {
        jeu.executerGraphique();
    }

    delete grille;

    return 0;
}

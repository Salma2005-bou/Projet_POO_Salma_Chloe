#include <iostream>
#include <vector>

#include "GrilleNormale.h"
#include "RegleConway.h"
#include "Afficheur.h"
#include "AfficheurConsole.h"
#include "AfficheurGraphique.h"
#include "JeudelaVie.h"
#include "EtatVivant.h"
#include "EtatMort.h"

using namespace std;

int main() {

    string nomFichier;
    cout << "Nom du fichier  : ";
    cin >> nomFichier;

    int choixMode;
    cout << "Choisissez le mode d'affichage :" << endl;
    cout << "1. Console" << endl;
    cout << "2. Graphique (SFML)" << endl;
    cout << "Votre choix : ";
    cin >> choixMode;

    // Lire matrice depuis fichier
    vector<vector<bool>> matrice;
    Fichier f;

    if (!f.lireMatrice(nomFichier, matrice)) {
        cout << "Erreur fichier" << endl;
        return 1;
    }

    int hauteur = matrice.size();
    int largeur = matrice[0].size();

    Regle* regle = new RegleConway();
    GrilleNormale* grille = new GrilleNormale(largeur, hauteur, regle);

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

    JeuDeLaVie jeu(grille, regle, afficheur);
    jeu.initialiserGrilleDepuisFichier(nomFichier);

    // MODE CONSOLE
    if (choixMode == 1) {
        int iterations;
        cout << "Nombre d'iterations : ";
        cin >> iterations;

        jeu.executer(iterations);
    }
    // MODE GRAPHIQUE
    else {
        int nb;
        cout << "Nombre d'iterations (0 = infini) : ";
        cin >> nb;

        if (nb == 0) nb = -1;

        // APPEL DIRECT A L’AFFICHEUR GRAPHIQUE
        afficheur->afficher(grille, nb);
    }

    delete grille;
    delete regle;
    delete afficheur;

    return 0;
}

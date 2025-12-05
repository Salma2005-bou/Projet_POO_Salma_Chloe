#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Grille.h"
#include "Regle.h"
#include "Afficheur.h"
#include "Fichier.h"

class JeuDeLaVie {
private:
    Grille* grille;           // Grille contenant toutes les cellules (propriété hors classe)
    Regle* regle;             // Règle (propriété hors classe)
    Afficheur* afficheur;     // Afficheur (propriété hors classe)
    int nombreIterations;     // variable utilitaire si besoin
public:
    // Constructeur
    JeuDeLaVie(Grille* g, Regle* r, Afficheur* a)
        : grille(g), regle(r), afficheur(a), nombreIterations(0) {}

    // Initialise la grille à partir d'un fichier (délégué à Fichier)
    void initialiserGrilleDepuisFichier(const std::string& nomFichier) {
        Fichier fichier;
        std::vector<std::vector<bool>> matrice;
        if (fichier.lireMatrice(nomFichier, matrice)) {
            // Vérifier que la matrice a les bonnes dimensions
            if ((int)matrice.size() != grille->getHauteur() ||
                (int)matrice[0].size() != grille->getLargeur()) {
                std::cerr << "Attention : dimensions du fichier ne correspondent pas à la grille." << std::endl;
                // Optionnel : redimensionner ou adapter ; ici on utilise la matrice telle quelle si compatible
            }
            grille->initialiserDepuisMatrice(matrice);
        } else {
            std::cerr << "Erreur lors de la lecture du fichier : " << nomFichier << std::endl;
        }
    }

    // Exécute le jeu en mode console (ou mode général) en déléguant à l'afficheur
    // L'afficheur doit gérer la boucle si la signature le permet (afficher(grille, nbIterations))
    void executer(int iterations) {
        // Si l'afficheur implémente l'itération interne, simplement déléguer :
        afficheur->afficher(grille, iterations);

        // Si tu préfères que JeuDeLaVie fasse la boucle toi-même, remplace par l'ancienne logique.
        // Exemple (commenté) :
        /*
        for (int i = 0; i < iterations; ++i) {
            std::cout << "Generation n°" << i << std::endl;
            afficheur->afficher(grille, 1); // afficher un seul pas si l'afficheur supporte "1"
            sauvegarderGeneration(i);
            grille->calculerGenerationSuivante();
            grille->appliquerGenerationSuivante();
        }
        */
    }

    // Exécute le mode graphique : délégation à l'afficheur (qui gère nbIterations)
    void executerGraphique(int nbIterations) {
        afficheur->afficher(grille, nbIterations);
    }

    // Sauvegarde la grille dans un fichier (format matrice de 0/1)
    void sauvegarderDansFichier(const std::string& nomFichier) {
        Fichier fichier;
        std::vector<std::vector<bool>> matrice(
            grille->getHauteur(),
            std::vector<bool>(grille->getLargeur(), false)
        );

        for (int i = 0; i < grille->getHauteur(); ++i) {
            for (int j = 0; j < grille->getLargeur(); ++j) {
                Cellule* c = grille->getCellule(i, j);
                if (c && c->getEtat())
                    matrice[i][j] = c->getEtat()->estVivante();
                else
                    matrice[i][j] = false; // sécurité si cellule non initialisée
            }
        }

        if (!fichier.sauvegarderMatrice(nomFichier, matrice)) {
            std::cerr << "Erreur lors de la sauvegarde dans le fichier : " << nomFichier << std::endl;
        }
    }

    // Sauvegarde nommée par numéro de génération
    void sauvegarderGeneration(int numero) {
        std::string nom = "Etats/generation_" + std::to_string(numero) + ".txt";
        std::cout << "Sauvegarde de : " << nom << std::endl;
        sauvegarderDansFichier(nom);
    }
};

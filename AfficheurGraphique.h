#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Afficheur.h"
#include "Grille.h"
#include "Fichier.h"

class AfficheurGraphique : public Afficheur {
public:
    void afficher(Grille* grille, int nbIterations = -1) override {

        const int largeurCellule = 20;
        const int hauteurCellule = 20;

        int hauteur = grille->getHauteur();
        int largeur = grille->getLargeur();

        sf::RenderWindow window(
            sf::VideoMode(largeur * largeurCellule, hauteur * hauteurCellule),
            "Jeu de la Vie"
        );

        // Pré-création des rectangles
        std::vector<std::vector<sf::RectangleShape>> rectangles(hauteur,
            std::vector<sf::RectangleShape>(largeur)
        );
        for (int i = 0; i < hauteur; ++i)
            for (int j = 0; j < largeur; ++j)
                rectangles[i][j] = sf::RectangleShape(sf::Vector2f(largeurCellule - 1, hauteurCellule - 1)),
                rectangles[i][j].setPosition(j * largeurCellule, i * hauteurCellule);

        int iteration = 0;
        Fichier fichier;

        while (window.isOpen()) {

            // Gestion événements
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
            }

            window.clear(sf::Color(255, 220, 235));

            // Dessin cellules
            for (int i = 0; i < hauteur; ++i)
                for (int j = 0; j < largeur; ++j)
                    rectangles[i][j].setFillColor(
                        grille->getCellule(i, j)->estVivante() ? sf::Color(230, 120, 155) : sf::Color(255, 235, 245)),
                    window.draw(rectangles[i][j]);

            window.display();

            // Sauvegarde génération
            std::vector<std::vector<bool>> matrice(hauteur, std::vector<bool>(largeur));
            for (int i = 0; i < hauteur; ++i)
                for (int j = 0; j < largeur; ++j)
                    matrice[i][j] = grille->getCellule(i, j)->estVivante();

            std::string nomFichier = "Etats/generation_" + std::to_string(iteration) + ".txt";
            fichier.sauvegarderMatrice(nomFichier, matrice);

            // Sauvegarde état avant génération suivante
            std::vector<std::vector<bool>> etatAvant = matrice;

            // Calcul + application génération suivante
            grille->calculerGenerationSuivante();
            grille->appliquerGenerationSuivante();

            // Vérification stabilité
            bool stable = true;
            for (int i = 0; i < hauteur && stable; i++)
                for (int j = 0; j < largeur && stable; j++)
                    if (grille->getCellule(i, j)->estVivante() != etatAvant[i][j])
                        stable = false;

            if (stable) {
                // Message console
                std::cout << "La grille est devenue stable à l'itération " << iteration << " " << std::endl;

                // Message SFML
                sf::Font font;
                if (font.loadFromFile("arial.ttf")) { // vérifier que arial.ttf est dans ton dossier
                    sf::Text texte;
                    texte.setFont(font);
                    texte.setString("Grille stable à l'iteration " + std::to_string(iteration));
                    texte.setCharacterSize(24);
                    texte.setFillColor(sf::Color::Red);
                    texte.setPosition(10, 10);

                    window.clear(sf::Color(255, 220, 235));
                    window.draw(texte);
                    window.display();
                }

                // Pause pour que l'utilisateur voie le message
                sf::sleep(sf::seconds(2));

                window.close();
                break;
            }

            iteration++;

            // Arrêt si nbIterations atteint
            if (nbIterations > 0 && iteration >= nbIterations) {
                window.close();
                break;
            }

            sf::sleep(sf::milliseconds(200));
        }
    }

    ~AfficheurGraphique() override {}
};

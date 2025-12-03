#pragma once
#include <iostream>
using namespace std;

#include "Afficheur.h"
#include "Grille.h"
#include <SFML/Graphics.hpp>

class AfficheurGraphique : public Afficheur {
public:
    void afficher(Grille* grille) override {
        const int largeurCellule = 20;
        const int hauteurCellule = 20;
        
        sf::RenderWindow window(sf::VideoMode(grille->getLargeur() * largeurCellule,
                                              grille->getHauteur() * hauteurCellule),
                                "Jeu de la Vie");

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color(255, 220, 235));

            for (int i = 0; i < grille->getHauteur(); ++i) {
                for (int j = 0; j < grille->getLargeur(); ++j) {
                    sf::RectangleShape cellule(sf::Vector2f(largeurCellule - 1, hauteurCellule - 1));
                    cellule.setPosition(j * largeurCellule, i * hauteurCellule);

                    if (grille -> getCellule(i, j) -> estVivante()) {
                        cellule.setFillColor(sf::Color(230, 120, 155));
                    } else {
                        cellule.setFillColor(sf::Color(255, 235, 245));
                    }

                    window.draw(cellule);
                }
            }

            window.display();
            grille->calculerGenerationSuivante();
            grille->appliquerGenerationSuivante();
            sf::sleep(sf::milliseconds(500));  // pause pour voir l’évolution
        }
    }

    ~AfficheurGraphique() override {}
};

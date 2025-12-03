class Afficheur {
    public:
        virtual void afficher ( Grille *grille ) = 0;
        virtual ~Afficheur() {}
};
class AfficheurConsole : public Afficheur {
    public:
        void afficher ( Grille *grille ) override {
            for (int i = 0; i < grille->getHauteur(); ++i) {
                for (int j = 0; j < grille->getLargeur(); ++j) {
                    if (grille->estVivante(i, j)) {
                        std::cout << "O ";
                    } else {
                        std::cout << ". ";
                    }
                }
                std::cout << std::endl;
            }
        }
        ~AfficheurConsole() override {}
};
class AfficheurGraphique : public Afficheur {
public:
    void afficher(Grille* grille) override {
        const int largeurCellule = 10;// largeur en pixels
        const int hauteurCellule = 10;// hauteur en pixels 
        // Crée une fenetre SFML 
        // le titre de la fenetre est "Jeu de la Vie"
        sf::RenderWindow window(sf::VideoMode(grille->getLargeur() * largeurCellule,
                                              grille->getHauteur() * hauteurCellule),
                                "Jeu de la Vie");
        // Boucle principale de la fenetre
        while (window.isOpen()) {
            sf::Event event; //Variable pour gérer les événements(clavier, souris, fermeture de la fenêtre, etc.)
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)// Si l'événement est une fermeture de fenêtre
                    window.close(); // ferme la fenêtre
            }

            window.clear(sf::Color::White); // fond blanc

            for (int i = 0; i < grille->getHauteur(); ++i) {
                for (int j = 0; j < grille->getLargeur(); ++j) {
                    sf::RectangleShape cellule(sf::Vector2f(largeurCellule - 1, hauteurCellule - 1));
                    cellule.setPosition(j * largeurCellule, i * hauteurCellule);

                    if (grille->estVivante(i, j)) {
                        cellule.setFillColor(sf::Color::Black); // cellule vivante
                    } else {
                        cellule.setFillColor(sf::Color::White); // cellule morte
                    }

                    window.draw(cellule);
                }
            }

            window.display();
        }
    }

    ~AfficheurGraphique() override {}
};

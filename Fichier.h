#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Fichier {
public:
    // lire une matrice depuis la premiere ligne de fichier
    bool lireMatrice(const string& nomFichier, vector<vector<bool>>& matrice) {
        ifstream fichier(nomFichier);
        if (!fichier.is_open()) {
            cerr << "Erreur lors de l'ouverture du fichier : " << nomFichier << endl;   
            return false;
        }
        
        int lignes, colonnes;
        fichier >> lignes >> colonnes; // lire la premiere ligne
        
        // Vérifier que les dimensions sont valides
        if (lignes <= 0 || colonnes <= 0) {
            cerr << "Erreur : dimensions invalides dans le fichier" << endl;
            fichier.close();
            return false;
        }
        
        // initialiser la matrice 
        matrice.resize(lignes, vector<bool>(colonnes, false));
        
        // Lire les valeurs pour remplir la matrice
        for (int i = 0; i < lignes; ++i) {
            for (int j = 0; j < colonnes; ++j) {
                int valeur;
            
                if (!(fichier >> valeur)) {
                    cerr << "Erreur : format de fichier incorrect ou données manquantes" << endl;
                    fichier.close();
                    return false;
                }
                // Vérifier que la valeur est bien 0 ou 1
                if (valeur != 0 && valeur != 1) {
            cerr << "Erreur : valeur invalide (" << valeur 
                 << ") à la position (" << i << ", " << j 
                 << "). Le fichier doit contenir uniquement 0 et 1." 
                 << endl;
            fichier.close();
            return false;
        }
                matrice[i][j] = (valeur == 1); // 1 pour true, 0 pour false
            }
        }
        
        fichier.close();
        return true;
    }
    /// Sauvegarder une matrice dans un fichier
    bool sauvegarderMatrice(const string& nomFichier, const vector<vector<bool>>& matrice) {
        ofstream fichier(nomFichier);
        if (!fichier.is_open()) {
            cerr << "Erreur lors de l'ouverture du fichier pour écriture : " << nomFichier << endl;
            return false;
        }

        int lignes = matrice.size();
        int colonnes = (lignes > 0) ? matrice[0].size() : 0;

        // Écrire les dimensions en première ligne
        fichier << lignes << " " << colonnes << endl;

        // Écrire les valeurs de la matrice
        for (int i = 0; i < lignes; ++i) {
            for (int j = 0; j < colonnes; ++j) {
                fichier << (matrice[i][j] ? 1 : 0) << " ";
            }
            fichier << endl;
        }

        fichier.close();
        return true;
    }
};
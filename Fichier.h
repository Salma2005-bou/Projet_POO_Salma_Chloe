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
                
                matrice[i][j] = (valeur == 1); // 1 pour true, 0 pour false
            }
        }
        
        fichier.close();
        return true;
    }
};
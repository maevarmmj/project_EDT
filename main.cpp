#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "enseignant.h"
#include "controllerEnseignant.h"


// Fonction pour créer un fichier CSV
void createCSV(const std::string& fileName, const std::vector<std::string>& headers, const std::vector<std::vector<std::string>>& data) {
    // Ouvrir le fichier en mode écriture
    std::ofstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible de créer le fichier " << fileName << std::endl;
        return;
    }

    // Écrire les en-têtes
    for (size_t i = 0; i < headers.size(); ++i) {
        file << headers[i];
        if (i < headers.size() - 1) file << ","; // Ajouter une virgule sauf pour le dernier élément
    }
    file << "\n";

    // Écrire les données
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) file << ","; // Ajouter une virgule sauf pour le dernier élément
        }
        file << "\n";
    }

    file.close();
    std::cout << "Fichier CSV cree avec succes : " << fileName << std::endl;
}

int main() {
    std::string fileName = "Enseignant.csv";
    std::vector<std::string> headers = {"Nom", "Prenom"};
    std::vector<std::vector<std::string>> data = {
        {"Trenchant", "Vincent"},
        {"Bertolim", "Maria-Alice"},
        {"Morlet", "Lucas"},
        {"Thomas", "Eric"},
        {"Desarmenien", "Tom"},
        {"Schlinquer", "Thomas"},
        {"Belghouthi", "Rabeb"},
        {"Boubaker", "Mohamed Bader"},
        {"Soulas","Celine"}
    };

    createCSV(fileName, headers, data);

    return 0;
}

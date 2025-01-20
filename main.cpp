#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <filesystem>

// Fonction pour vérifier si un fichier existe
bool fileExists(const std::string& fileName) {
    return std::filesystem::exists(fileName);
}

// Fonction pour créer un fichier CSV avec des en-têtes
void createCSV(const std::string& fileName, const std::vector<std::string>& headers) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible de créer le fichier " << fileName << std::endl;
        return;
    }

    // Écrire les en-têtes
    for (size_t i = 0; i < headers.size(); ++i) {
        file << headers[i];
        if (i < headers.size() - 1) file << ",";
    }
    file << "\n";
    file.close();
    std::cout << "Fichier CSV créé avec succès : " << fileName << std::endl;
}

// Fonction pour lire le fichier CSV et stocker les données
std::vector<std::vector<std::string>> readCSV(const std::string& fileName) {
    std::vector<std::vector<std::string>> data;
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << fileName << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        if (!row.empty()) {
            data.push_back(row);
        }
    }

    file.close();
    return data;
}

// Fonction pour écrire les données dans le fichier CSV
void writeCSV(const std::string& fileName, const std::vector<std::vector<std::string>>& data) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible d'ecrire dans le fichier " << fileName << std::endl;
        return;
    }

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) file << ",";
        }
        file << "\n";
    }

    file.close();
}

// Fonction pour ajouter ou modifier un enseignant
void addOrUpdateEntry(const std::string& fileName, const std::vector<std::string>& headers, const std::string& nom, const std::string& prenom) {
    // Vérification et création du fichier s'il n'existe pas
    if (!fileExists(fileName)) {
        createCSV(fileName, headers);
    }

    auto data = readCSV(fileName);
    bool found = false;

    // Mise à jour si le nom existe déjà
    for (auto& row : data) {
        if (row.size() >= 2 && row[0] == nom) {
            row[1] = prenom;
            found = true;
            break;
        }
    }

    if (!found) {
        data.push_back({nom, prenom});  // Ajouter une nouvelle ligne si non trouvée
    }

    writeCSV(fileName, data);
}

int main() {
    std::string fileName = "Enseignant.csv";
    std::vector<std::string> headers = {"Nom", "Prenom"};

    // Ajout et mise à jour des enseignants
    addOrUpdateEntry(fileName, headers, "Trenchant", "Vincent");
    addOrUpdateEntry(fileName, headers, "Morlet", "Lucas");
    addOrUpdateEntry(fileName, headers, "Schlinquer", "Thomas");
    addOrUpdateEntry(fileName, headers, "Bertolim", "Maria-Alice");
    addOrUpdateEntry(fileName, headers, "Thomas", "Eric");
    addOrUpdateEntry(fileName, headers, "Desarmenien", "Tom");
    addOrUpdateEntry(fileName, headers, "Belghouthi", "Rabeb");
    addOrUpdateEntry(fileName, headers, "Boubaker", "Mohamed Bader");
    addOrUpdateEntry(fileName, headers, "Soulas", "Celine");
    addOrUpdateEntry(fileName, headers, "Vaulot", "Loulou");

    std::cout << "Mise a jour du fichier terminee." << std::endl;
    return 0;
}

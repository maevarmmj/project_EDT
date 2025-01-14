#include "enseignant.h"

// Constructeur par défaut
Enseignant::Enseignant() : nom(""), prenom("") {}

// Constructeur avec paramètres
Enseignant::Enseignant(const std::string& nom, const std::string& prenom)
    : nom(nom), prenom(prenom) {}

// Accesseur pour le nom
std::string Enseignant::getNom() const {
    return nom;
}

// Accesseur pour le prénom
std::string Enseignant::getPrenom() const {
    return prenom;
}

// Méthode pour afficher le nom et le prénom de l'enseignant
void Enseignant::affiche() const {
    std::cout << prenom << " " << nom << std::endl;
}

// Destructeur
Enseignant::~Enseignant() {}

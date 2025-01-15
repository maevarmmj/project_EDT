#include "enseignant.h"

Enseignant::Enseignant() : nom(""), prenom("") {}

Enseignant::Enseignant(const std::string& nom, const std::string& prenom)
    : nom(nom), prenom(prenom) {}

std::string Enseignant::getNom() const {
    return nom;
}

std::string Enseignant::getPrenom() const {
    return prenom;
}

void Enseignant::affiche() const {
    std::cout << prenom << " " << nom << std::endl;
}

Enseignant::~Enseignant() {}

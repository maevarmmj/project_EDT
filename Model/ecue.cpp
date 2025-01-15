#include "ecue.h"

Ecue::Ecue() : etudiants(), enseignant() {
    this->nom = "";
    this->nbHeure = 0;
}

Ecue::Ecue(std::string nom, int nbHeure, GroupeEtudiant etudiants, Enseignant enseignant)
{
    this->nom = nom;
    this->nbHeure = nbHeure;
    this->etudiants = etudiants;
    this->enseignant = enseignant;
}


std::string Ecue::getNom() const {
    return nom;
}

uint32 Ecue::getNbHeure() const {
    return nbHeure;
}

GroupeEtudiant Ecue::getEtudiants() const {
    return etudiants;
}

Enseignant Ecue::getEnseignant() const {
    return enseignant;
}

cours Ecue::getTypeSalle() const {
    return typeSalle;
}

uint32* Ecue::getHeureTotal(){
    return heureTotal;
}

uint32* Ecue::getHeureRest() {
    return heureRest;
}

// Setters
void Ecue::setNom(const std::string& nom) {
    this->nom = nom;
}

void Ecue::setNbHeure(uint32 nbHeure) {
    this->nbHeure = nbHeure;
}

void Ecue::setEtudiants(const GroupeEtudiant& etudiants) {
    this->etudiants = etudiants;
}

void Ecue::setEnseignant(const Enseignant& enseignant) {
    this->enseignant = enseignant;
}

void Ecue::setTypeSalle(cours typeSalle) {
    this->typeSalle = typeSalle;
}

void Ecue::setHeureTotal(const uint32 heures[5]) {
    for (int i = 0; i < 5; ++i) {
        heureTotal[i] = heures[i];
    }
}

void Ecue::setHeureRest(const uint32 heures[5]) {
    for (int i = 0; i < 5; ++i) {
        heureRest[i] = heures[i];
    }
}

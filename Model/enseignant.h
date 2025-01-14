#ifndef ENSEIGNANT_H
#define ENSEIGNANT_H

#include <string>
#include <iostream>

class Enseignant {
private:
    std::string nom;       // Nom de l'enseignant
    std::string prenom;    // Prénom de l'enseignant

public:
    // Constructeur par défaut
    Enseignant();

    // Constructeur avec paramètres
    Enseignant(const std::string& nom, const std::string& prenom);

    // Accesseurs en lecture
    std::string getNom() const;
    std::string getPrenom() const;

    // Méthode affiche
    void affiche() const;

    // Destructeur
    ~Enseignant();
};

#endif // ENSEIGNANT_H

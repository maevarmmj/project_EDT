#ifndef ENSEIGNANT_H
#define ENSEIGNANT_H

#include <string>
#include <iostream>

class Enseignant {
private:
    std::string nom;    
    std::string prenom;   

public:
    Enseignant();

    Enseignant(const std::string& nom, const std::string& prenom);

    std::string getNom() const;
    std::string getPrenom() const;

    void affiche() const;

    ~Enseignant();
};

#endif // ENSEIGNANT_H

#ifndef SEMAINE_H
#define SEMAINE_H

#include <vector>      // Pour std::vector
#include "Creneau.h"
#include "main.h"// Inclusion de la classe Creneau

class Semaine {
private:
    uint32 numero;                      // Numéro de la semaine
    std::vector<Creneau> listeCreneau;    // Liste dynamique de créneaux

public:
    Semaine();
    Semaine(uint32 numero);

    uint32 getNumero() const;
    const std::vector<Creneau>& getListeCreneau() const;

    void ajouterCreneau(const Creneau& creneau);  // Ajouter un créneau à la liste
    void supprimerCreneau(int index);            // Supprimer un créneau par index
};

#endif // SEMAINE_H

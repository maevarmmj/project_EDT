#ifndef SEMAINE_H
#define SEMAINE_H

#include <vector>      
#include "Creneau.h"
#include "main.h"

class Semaine {
private:
    uint32 numero;                   
    std::vector<Creneau> listeCreneau;   

public:
    Semaine();
    Semaine(uint32 numero);

    uint32 getNumero() const;
    const std::vector<Creneau>& getListeCreneau() const;

    void ajouterCreneau(const Creneau& creneau);  
    void supprimerCreneau(int index);        
};

#endif // SEMAINE_H

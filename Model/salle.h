#ifndef SALLE_H
#define SALLE_H
#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "definition.h"

class Salle
{
private:
    int numero;
    cours typeSalle;
    bool disponible;

public:
    Salle();
    Salle(int numero,cours typeSalle);
    int getNumero() const;
    cours getTypeSalle() const;
    void setTypeSalle(cours typeSalle);
    bool estdisponible();
    void setDisponible(bool disponible);

    void deleteSalle();
    void affiche();
};

#endif // SALLE_H

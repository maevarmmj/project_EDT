#ifndef SALLE_H
#define SALLE_H

#include "definition.h"

class Salle
{
private:
    int numero;
    cours typeSalle;

public:
    Salle();
    Salle(int numero,cours typeSalle);
    int getNumero() const;
    cours getTypeSalle() const;
    void setTypeSalle(cours typeSalle);

    void deleteSalle();
    void affiche();
};

#endif // SALLE_H

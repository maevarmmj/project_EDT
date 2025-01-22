#include "salle.h"


Salle::Salle() : numero(0), typeSalle(CM), disponible(true)
{

}


Salle::Salle(int numero, cours typeSalle) : numero(numero), typeSalle(typeSalle), disponible(true)
{
}

int Salle::getNumero() const
{
    return numero;
}


cours Salle::getTypeSalle() const
{
    return typeSalle;
}

void Salle::setTypeSalle(cours typeSalle)
{
    this->typeSalle=typeSalle;
}

void Salle::deleteSalle() {
    numero = 0;
    typeSalle = CM;
}

bool Salle::estdisponible()
{
    return disponible;
}

void Salle::setDisponible(bool disponible)
{
    this->disponible=disponible;
}


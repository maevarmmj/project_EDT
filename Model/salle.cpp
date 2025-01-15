#include "Salle.h"


Salle::Salle() : numero(0), typeSalle("")
{
    this->numero=0;
    this->typeSalle="";

}


Salle::Salle(int numero, std::string typeSalle) : numero(numero), typeSalle(typeSalle)
{
    this->numero=numero;
    this->typeSalle=typeSalle;
}

int Salle::getNumero()
{
    return numero;
}


std::string Salle::getTypeSalle()
{
    return typeSalle;
}

void Salle::setTypeSalle()
{
    this->typeSalle=typeSalle;
}

void Salle::deleteSalle() {
    numero = 0;
    typeSalle = "";
}

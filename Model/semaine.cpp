#include "Semaine.h"

Semaine::Semaine() : listeCreneau() {
    this->numero = 0;
}

Semaine::Semaine(uint32 numero) {
    this->numero = 0;
    this->listeCreneau = listeCreneau;
}

uint32 Semaine::getNumero() const {
    return numero;
}

const std::vector<Creneau>& Semaine::getListeCreneau() const {
    return listeCreneau;
}


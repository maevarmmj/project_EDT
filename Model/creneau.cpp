#include "creneau.h"

Creneau::Creneau() = default;

Creneau::Creneau(time_t jourHeure, Salle salle, Ecue ecue){
    this->jourHeure = jourHeure;
    this->salle = salle;
    this->ecue = ecue;
}

Creneau::~Creneau()=default;

time_t Creneau::getJourHeure(){
    return this->jourHeure;
}

Salle Creneau::getSalle(){
    return this->salle;
}

Ecue Creneau::getEcue(){
    return this->ecue;
}

void Creneau::setJourHeure(time_t jourHeure){
    this->jourHeure = jourHeure;
}

void Creneau::setSalle(Salle salle){
    this->salle = salle;
}

void Creneau::setEcue(Ecue ecue){
    this->ecue = ecue;
}

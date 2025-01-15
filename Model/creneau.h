#ifndef CRENEAU_H
#define CRENEAU_H

#include <ctime>
#include "Model/salle.h"
#include "Model/ecue.h"

class Creneau
{
private :
    time_t jourHeure;
    Salle salle;
    Ecue ecue;
public:
    Creneau();
    Creneau(time_t jourHeure, Salle salle, Ecue ecue);
    ~Creneau();
    time_t getJourHeure();
    Salle getSalle();
    Ecue getEcue();
    void setJourHeure(time_t jourHeure);
    void setSalle(Salle salle);
    void setEcue(Ecue ecue);

};

#endif // CRENEAU_H

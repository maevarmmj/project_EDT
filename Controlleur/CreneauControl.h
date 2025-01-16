#ifndef CRENEAUCONTROL_H
#define CRENEAUCONTROL_H

#include <QFile>
#include <QTextStream>
#include <QDir>
#include "Model/creneau.h"

tm setJourHeure(int jourSemaine, int heure);
int salleLibreHeure(int heure);

#endif // CRENEAUCONTROL_H

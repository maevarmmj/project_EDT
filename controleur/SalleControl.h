#ifndef SALLECONTROL_H
#define SALLECONTROL_H

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QDir>

#include "Model/salle.h"
#include "definition.h"

bool ajouterSalleCSV(int numero, cours cours);
bool retirerSalleCSV(int numero);

#endif // SALLECONTROL_H

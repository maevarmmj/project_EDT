#ifndef SALLECONTROL_H
#define SALLECONTROL_H

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QDir>

#include "Model/salle.h"
#include "Controleur/CreneauControl.h"
#include "definition.h"

CreationResult ajouterSalleCSV(int numero, cours cours);
SuppressionResult retirerSalleCSV(int numero);
QList<int> readRoomNumbersFromCSV(const QString& typeCours);

#endif // SALLECONTROL_H

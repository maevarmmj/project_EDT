#ifndef ENSEIGNANTCONTROL_H
#define ENSEIGNANTCONTROL_H


#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QDir>
#include <string>

#include "Model/enseignant.h"
#include "definition.h"

bool ajouterEnseignantCSV(const std::string& nom, const std::string& prenom);
bool retirerEnseignantCSV(const std::string& nom, const std::string& prenom);


#endif // ENSEIGNANTCONTROL_H

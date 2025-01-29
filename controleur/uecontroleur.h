#ifndef UECONTROLEUR_H
#define UECONTROLEUR_H

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QDir>

#include "Model/groupeetudiant.h"
#include "Controleur/CreneauControl.h"
#include "definition.h"

CreationResult ajouterUECSV(const std::string& nomUE, std::vector<>);
SuppressionResult retirerUECSV(const std::string& nomUE);



#endif // UECONTROLEUR_H

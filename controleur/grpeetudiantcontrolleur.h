#define GRPEETUDIANTCONTROLLEUR_H
#include <fstream>
#include <iostream>
#include <string>


#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QDir>

#include "Model/groupeetudiant.h"
#include "Controleur/CreneauControl.h"
#include "definition.h"

CreationResult ajouterGroupeEtudiantCSV(const std::string& nomGroupe);
SuppressionResult retirerGroupeEtudiantCSV(const std::string& nomGroupe);


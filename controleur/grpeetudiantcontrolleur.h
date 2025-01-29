#define GRPEETUDIANTCONTROLLEUR_H
#include <Model/groupeetudiant.h>
#include <fstream>
#include <iostream>
#include <string>


#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QDir>

#include "Model/groupeetudiant.h"
#include "definition.h"

CreationResult ajouterGroupeEtudiantCSV(const std::string& nomGroupe);
bool retirerGroupeEtudiantCSV(const std::string& nomGroupe);


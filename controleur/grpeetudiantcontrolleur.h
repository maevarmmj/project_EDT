#define GRPEETUDIANTCONTROLLEUR_H

#include "Model/groupeetudiant.h"
#include "Controleur/CreneauControl.h"
#include "definition.h"

CreationResult ajouterGroupeEtudiantCSV(const std::string& nomGroupe);
SuppressionResult retirerGroupeEtudiantCSV(const std::string& nomGroupe);


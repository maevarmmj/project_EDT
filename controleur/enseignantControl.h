#ifndef ENSEIGNANTCONTROL_H
#define ENSEIGNANTCONTROL_H

#include "Model/enseignant.h"
#include "Controleur/CreneauControl.h"
#include "definition.h"

CreationResult ajouterEnseignantCSV(const std::string& nom, const std::string& prenom);
SuppressionResult retirerEnseignantCSV(const std::string& nom, const std::string& prenom);


#endif // ENSEIGNANTCONTROL_H

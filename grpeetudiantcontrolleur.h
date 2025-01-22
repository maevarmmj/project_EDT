#ifndef GRPEETUDIANTCONTROLLEUR_H
#define GRPEETUDIANTCONTROLLEUR_H
#include <Model/groupeetudiant.h>
#include <fstream>
#include <iostream>
#include <string>

class grpeetudiantcontrolleur
{
public:
    grpeetudiantcontrolleur();
    static void enregistrerDansCSV(const GroupeEtudiant groupe, const std::string cheminFichier);
};

#endif // GRPEETUDIANTCONTROLLEUR_H

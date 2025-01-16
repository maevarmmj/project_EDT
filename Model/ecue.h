#ifndef ECUE_H
#define ECUE_H

#include <fstream>
#include <vector>
#include <iostream>
#include <string>

#include "main.h"
#include <string>
#include "enseignant.h"
#include "groupeetudiant.h"

class Ecue
{
private:
    std::string nom;
    uint32 nbHeure;
    GroupeEtudiant etudiants;
    Enseignant enseignant;
    cours typeSalle;
    uint32 heureTotal[5];
    uint32 heureRest[5];

public:
    Ecue();
    Ecue(std::string nom, int nbHeure, GroupeEtudiant etudiants, Enseignant enseignant);
    std::string getNom() const;
    uint32 getNbHeure() const;
    GroupeEtudiant getEtudiants() const;
    Enseignant getEnseignant() const;
    cours getTypeSalle() const;
    uint32* getHeureTotal();
    uint32* getHeureRest();

    void setNom(const std::string& nom);
    void setNbHeure(uint32 nbHeure);
    void setEtudiants(const GroupeEtudiant& etudiants);
    void setEnseignant(const Enseignant& enseignant);
    void setTypeSalle(cours typeSalle);
    void setHeureTotal(const uint32 heures[5]);
    void setHeureRest(const uint32 heures[5]);

    std::vector<GroupeEtudiant> lireGroupesDepuisCSV(const std::string& cheminFichier);
    GroupeEtudiant choisirGroupe(std::vector<GroupeEtudiant>& groupes);

    void ajouterECUE();




};

#endif // ECUE_H



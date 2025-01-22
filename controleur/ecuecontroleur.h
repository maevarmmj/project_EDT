#ifndef ECUECONTROLEUR_H
#define ECUECONTROLEUR_H

#include "Model/ecue.h"

class EcueControleur
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
    EcueControleur();
    EcueControleur(std::string nom, int nbHeure, GroupeEtudiant etudiants, Enseignant enseignant);


    std::vector<GroupeEtudiant> lireGroupesEtudiantCSV(QString& cheminFichier);
    std::vector<Salle> lireSallesCSV(QString& cheminFichier);
    std::vector<Enseignant> lireEnseignantCSV(QString& cheminFichier);


    // Fonctions pour ajouter des informations à l'ECUE
    boolean ajouterEnseignantCSV(const std::string& nom, const std::string& prenom);
    boolean ajouterSalleCSV(int numero, const cours typeSalle);
    boolean ajouterGroupeCSV(const std::string& groupe);

    // Fonction pour créer un ECUE avec les informations provenant des fichiers CSV
    void creerECUE(const std::string& nomECUE, const std::string& nom, const std::string& prenom, int numero, const cours& typeSalle, const std::string& groupe);



};

#endif // ECUECONTROLEUR_H

#ifndef ECUECONTROLEUR_H
#define ECUECONTROLEUR_H

#include "Model/ecue.h"
#include "Controleur/CreneauControl.h"
#include "definition.h"
#include <QString>

class EcueControleur
{

private:
    std::string nom;
    uint32 nbHeuresTotales;
    uint32 nbHeuresTotalesAPlacer;
    GroupeEtudiant etudiants;
    Enseignant enseignant;
    cours typeSalle;
    std::vector<cours> typesCours;
    std::vector<int> heuresParCours;
    std::vector<int> heuresAPlacer;




public:
    EcueControleur();
    EcueControleur(const QString& nomECUE, const QString& nom, const QString& prenom, const QString& groupe, const QString& typesCours, const QString& heuresParCours, const QString& heuresAPlacer);

    std::vector<GroupeEtudiant> lireGroupesEtudiantCSV(QString& cheminFichier);
    std::vector<Salle> lireSallesCSV(QString& cheminFichier);
    std::vector<Enseignant> lireEnseignantCSV(QString& cheminFichier);

    boolean ajouterEnseignantCSV(const std::string& nom, const std::string& prenom);
    boolean ajouterSalleCSV(int numero, const cours typeSalle);
    boolean ajouterGroupeCSV(const std::string& groupe);

    void creerECUE(const std::string& nomECUE, const std::string& nom, const std::string& prenom, const std::vector<cours>& typesCours, const std::vector<int>& heuresParCours, const std::string& groupe);
    int getNombreHeure(const cours& typeCours) const;
    uint32 decrementerHeuresCours(const cours& typeCours, uint32 nbHeuresADecrementer);
    uint32 getNombreHeureTotal();
    uint32 getNombreHeureTotalAPlacer();

    bool retirerECUECSV(const std::string& nomECUE, const std::string& nom, const std::string& prenom, const std::string& groupe);

    std::string coursToString(const cours& typeCours) const;



};

#endif // ECUECONTROLEUR_H

#include "main.h"
#include <iostream>


int main() {
    EcueControleur ecue;

    std::string nomECUE = "TNS";
    std::string nomEnseignant = "Trenchant";
    std::string prenomEnseignant = "Vincent";
    std::string groupeEtudiant = "E4";

    std::vector<cours> types = {CM, TD, TP_INFO};
    std::vector<int> heures = {10, 20, 15};
    ecue.creerECUE(nomECUE, nomEnseignant, prenomEnseignant, types, heures, groupeEtudiant);

    int heuresCM = ecue.getNombreHeure(CM);
    std::cout << "Nombre d'heures pour CM : " << heuresCM << std::endl;

    int heuresTP = ecue.getNombreHeure(TP_ELEC);
    std::cout << "Nombre d'heures pour TP_ELEC : " << heuresTP << std::endl;

    int heuresTot = ecue.getNombreHeureTotal();
    std::cout << "Nombre d'heures totales : " << heuresTot << std::endl;
    int testDecrement = ecue.decrementerHeuresCours(CM, 3);
    int testDecrement2 = ecue.decrementerHeuresCours(CM, 4);
    int testDecrement3 = ecue.decrementerHeuresCours(TD, 14);
    int testDecrement4 = ecue.decrementerHeuresCours(TD, 15);


    std::cout << "Nombre d'heures a placer pour le CM (1) : " << testDecrement << std::endl;
    std::cout << "Nombre d'heures a placer pour le CM (2) : " << testDecrement2 << std::endl;
    std::cout << "Nombre d'heures a placer pour le TD (2) : " << testDecrement3 << std::endl;
    std::cout << "Nombre d'heures a placer pour le TD (2) : " << testDecrement4 << std::endl;
    std::cout << "Nombre d'heures a placer totales : " << ecue.getNombreHeureTotalAPlacer() << std::endl;


    EcueControleur ecue1;

    std::string nomECUE1 = "Maths";
    std::string nomEnseignant1 = "Bertolim";
    std::string prenomEnseignant1 = "M-A";
    std::string groupeEtudiant1 = "E4";

    std::vector<cours> types1 = {CM, EXAMEN, TP_INFO};
    std::vector<int> heures1 = {30, 10, 14};
    ecue1.creerECUE(nomECUE1, nomEnseignant1, prenomEnseignant1, types1, heures1, groupeEtudiant1);

    int heuresCM1 = ecue1.getNombreHeure(CM);
    std::cout << "Nombre d'heures pour CM : " << heuresCM1 << std::endl;

    int heuresTP1 = ecue1.getNombreHeure(TP_ELEC);
    std::cout << "Nombre d'heures pour TP_ELEC : " << heuresTP1 << std::endl;

    int heuresTot1 = ecue1.getNombreHeureTotal();
    std::cout << "Nombre d'heures totales : " << heuresTot1 << std::endl;
    int testDecrement5 = ecue1.decrementerHeuresCours(CM, 3);
    int testDecrement6 = ecue1.decrementerHeuresCours(CM, 4);
    int testDecrement7 = ecue1.decrementerHeuresCours(EXAMEN, 14);
    int testDecrement8 = ecue1.decrementerHeuresCours(TP_INFO, 15);


    std::cout << "Nombre d'heures a placer pour le CM (1) : " << testDecrement5 << std::endl;
    std::cout << "Nombre d'heures a placer pour le CM (2) : " << testDecrement6 << std::endl;
    std::cout << "Nombre d'heures a placer pour le EXAMEN (1) : " << testDecrement7 << std::endl;
    std::cout << "Nombre d'heures a placer pour le TP_INFO (2) : " << testDecrement8 << std::endl;
    std::cout << "Nombre d'heures a placer totales : " << ecue1.getNombreHeureTotalAPlacer() << std::endl;




    //ecue.retirerECUECSV(nomECUE, nomEnseignant, prenomEnseignant, groupeEtudiant);

    // ajouterSalleCSV(213, CM);
    // ajouterSalleCSV(200, TP_INFO);
    // ajouterSalleCSV(213, EXAMEN);
    // ajouterSalleCSV(103, CM);
    // retirerSalleCSV(213);
    // ajouterSalleCSV(213, EXAMEN);
    // retirerSalleCSV(551);
    // retirerSalleCSV(103);

    // retirerEnseignantCSV("Trenchant", "Vincent");
    // retirerEnseignantCSV("Schlinquer", "Thomas");

    // ajouterEnseignantCSV("Bertolim", "M-A");
    // ajouterEnseignantCSV("Trenchant", "Vincent");



    // ajouterGroupeEtudiantCSV("E1");
    // ajouterGroupeEtudiantCSV("E2");
    // ajouterGroupeEtudiantCSV("E3");
    // ajouterGroupeEtudiantCSV("E4");
    // ajouterGroupeEtudiantCSV("E5");


    salleLibreSemaine(3, roomNumbers);

    db.close();

    popupEdt *popup = new popupEdt();

    popup->show();





}

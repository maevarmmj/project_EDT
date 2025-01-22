#include "main.h"
#include <iostream>

#include <iostream>

int main() {
    EcueControleur ecue;

    std::string nomECUE = "Blabla";
    std::string nomEnseignant = "Trenchant";
    std::string prenomEnseignant = "Vincent";
    int numeroSalle = 101;
    cours typeSalle = CM;
    std::string groupeEtudiant = "E4";

    std::vector<cours> types = {CM, TD, TP_INFO};
    std::vector<int> heures = {10, 20, 15};
    ecue.creerECUE(nomECUE, nomEnseignant, prenomEnseignant, numeroSalle, types, heures, groupeEtudiant);

    int heuresCM = ecue.getNombreHeure(CM);
    std::cout << "Nombre d'heures pour CM : " << heuresCM << std::endl;

    int heuresTP = ecue.getNombreHeure(TP_ELEC);
    std::cout << "Nombre d'heures pour TP_ELEC : " << heuresTP << std::endl;


    return 0;
}

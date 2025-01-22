#include "main.h"
#include <iostream>

#include <iostream>

int main() {
    EcueControleur ecue;

    std::string nomECUE = "Blabla";
    std::string nomEnseignant = "Trenchant";
    std::string prenomEnseignant = "Vincent";
    int numeroSalle = 103;
    cours typeSalle = TD;
    std::string groupeEtudiant = "E4";

    std::cout << "Creation de l'ECUE en cours...\n";
    ecue.creerECUE(nomECUE, nomEnseignant, prenomEnseignant, numeroSalle, typeSalle, groupeEtudiant);

    return 0;
}

#include "grpeetudiantcontrolleur.h"


grpeetudiantcontrolleur::grpeetudiantcontrolleur() {}

void  grpeetudiantcontrolleur::enregistrerDansCSV(const GroupeEtudiant groupe, const std::string cheminFichier) {
    std::ofstream fichierCSV(cheminFichier, std::ios::app); // Ouvrir en mode ajout
    if (!fichierCSV.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << cheminFichier << std::endl;
        return;
    }

    // Écrire le nom du groupe dans le fichier CSV
    fichierCSV << groupe.getnomGroupe() << "\n";

    std::cout << "Le groupe " << groupe.getnomGroupe() << " a été enregistré dans le fichier " << cheminFichier << std::endl;

    fichierCSV.close();
}

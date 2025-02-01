#include "groupeetudiant.h"


GroupeEtudiant::GroupeEtudiant() : nomGroupe("Inconnu") {}

GroupeEtudiant::GroupeEtudiant(std::string nomGroupe) : nomGroupe(nomGroupe) {}


std::string GroupeEtudiant::getnomGroupe() const {
    return nomGroupe;
}


void GroupeEtudiant::deleteGroupe() {
    nomGroupe = ""; // On vide le nom du groupe
    std::cout << "Le groupe a été supprimé." << std::endl;
}
bool operator== (GroupeEtudiant &gp1, GroupeEtudiant &gp2){
    if (gp1.getnomGroupe() == gp2.getnomGroupe()){
        return true;
    }
    return false;
}

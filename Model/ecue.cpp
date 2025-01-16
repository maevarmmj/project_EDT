#include "ecue.h"

Ecue::Ecue() : etudiants(), enseignant() {
    this->nom = "";
    this->nbHeure = 0;
}

Ecue::Ecue(std::string nom, int nbHeure, GroupeEtudiant etudiants, Enseignant enseignant)
{
    this->nom = nom;
    this->nbHeure = nbHeure;
    this->etudiants = etudiants;
    this->enseignant = enseignant;
}


std::string Ecue::getNom() const {
    return nom;
}

uint32 Ecue::getNbHeure() const {
    return nbHeure;
}

GroupeEtudiant Ecue::getEtudiants() const {
    return etudiants;
}

Enseignant Ecue::getEnseignant() const {
    return enseignant;
}

cours Ecue::getTypeSalle() const {
    return typeSalle;
}

uint32* Ecue::getHeureTotal(){
    return heureTotal;
}

uint32* Ecue::getHeureRest(){
    return heureRest;
}

// Setters
void Ecue::setNom(const std::string& nom) {
    this->nom = nom;
}

void Ecue::setNbHeure(uint32 nbHeure) {
    this->nbHeure = nbHeure;
}

void Ecue::setEtudiants(const GroupeEtudiant& etudiants) {
    this->etudiants = etudiants;
}

void Ecue::setEnseignant(const Enseignant& enseignant) {
    this->enseignant = enseignant;
}

void Ecue::setTypeSalle(cours typeSalle) {
    this->typeSalle = typeSalle;
}

void Ecue::setHeureTotal(const uint32 heures[5]) {
    for (int i = 0; i < 5; ++i) {
        heureTotal[i] = heures[i];
    }
}

void Ecue::setHeureRest(const uint32 heures[5]) {
    for (int i = 0; i < 5; ++i) {
        heureRest[i] = heures[i];
    }
}


// POUR LIRE LE FICHIER CSV QUI CONTIENT LES GROUPES ETUDIANTS
std::vector<GroupeEtudiant> Ecue::lireGroupesDepuisCSV(const std::string& cheminFichier) {
    std::vector<GroupeEtudiant> groupes;
    std::ifstream fichier(cheminFichier);
    if (!fichier.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << cheminFichier << std::endl;
        return groupes;
    }

    std::string ligne;
    while (std::getline(fichier, ligne)) {
        if (!ligne.empty()) {
            groupes.emplace_back(GroupeEtudiant(ligne)); // Création d'un GroupeEtudiant à partir du nom
        }
    }
    fichier.close();
    return groupes;
}


// POUR AFFICHER ET CHOISIR UN GROUPE
GroupeEtudiant Ecue::choisirGroupe(std::vector<GroupeEtudiant>& groupes) {
    if (groupes.empty()) {
        std::cerr << "Aucun groupe disponible." << std::endl;
        return GroupeEtudiant("Groupe par défaut");
    }

    std::cout << "Liste des groupes disponibles :\n";
    for (size_t i = 0; i < groupes.size(); ++i) {
        std::cout << i + 1 << " - " << groupes[i].getnomGroupe() << std::endl;
    }

    size_t choix;
    do {
        std::cout << "Votre choix (1-" << groupes.size() << ") : ";
        std::cin >> choix;
        if (choix < 1 || choix > groupes.size()) {
            std::cerr << "Choix invalide. Veuillez réessayer." << std::endl;
        }
    } while (choix < 1 || choix > groupes.size());

    return groupes[choix - 1];
}




void Ecue::ajouterECUE() {
    std::string nomECUE;
    std::cout << "Nom de l'ECUE : ";
    std::cin.ignore(); 
    std::getline(std::cin, nomECUE);
    setNom(nomECUE);

    std::vector<GroupeEtudiant> groupes = lireGroupesDepuisCSV("groupes.csv");

    GroupeEtudiant groupeEtudiant = choisirGroupe(groupes);
    setEtudiants(groupeEtudiant);

    // std::string nomEnseignant;
    // std::string prenomEnseignant;
    // std::cout << "Nom enseignant : ";
    // std::getline(std::cin, nomEnseignant);
    // std::cout << "Prénom enseignant : ";
    // std::getline(std::cin, prenomEnseignant );
    // Enseignant enseignant = Enseignant(nomGroupeEtudiant, prenomEnseignant);
    // setEnseignant(enseignant);


    // int typeCoursChoisi;
    // std::cout << "Type de cours : ";
    // std::cout << "Choisissez le type de cours :\n";
    // std::cout << "1 - CM\n";
    // std::cout << "2 - TD\n";
    // std::cout << "3 - TP_INFO\n";
    // std::cout << "4 - TP_ELEC\n";
    // std::cout << "5 - EXAM\n";
    // std::cout << "Votre choix : ";
    // std::cin >> typeCoursChoisi;

    // cours typeCours;
    // uint32 nbHeures;

    // switch (typeCoursChoisi) {
    // case 1:
    //     typeCours = CM;
    //     std::cout << "Nombre d'heures CM : ";
    //     std::cin >> nbHeures;
    //     break;
    // case 2:
    //     typeCours = TD;
    //     std::cout << "Nombre d'heures TD : ";
    //     std::cin >> nbHeures;
    //     break;
    // case 3:
    //     typeCours = TP_INFO;
    //     std::cout << "Nombre d'heures TP INFO: ";
    //     std::cin >> nbHeures;
    //     break;
    // case 4:
    //     typeCours = TP_ELEC;
    //     std::cout << "Nombre d'heures TP ELEC: ";
    //     std::cin >> nbHeures;
    //     break;
    // case 5:
    //     typeCours = EXAMEN;
    //     std::cout << "Nombre d'heures EXAMEN : ";
    //     std::cin >> nbHeures;
    //     break;
    // default:
    //     std::cerr << "Choix invalide. Type de cours par défaut : CM." << std::endl;
    //     typeCours = CM;
    //     break;
    // }
    // setTypeSalle(typeCours);
}


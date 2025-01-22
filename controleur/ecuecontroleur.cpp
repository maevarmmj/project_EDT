#include "ecuecontroleur.h"

EcueControleur::EcueControleur() : etudiants(), enseignant() {
    this->nom = "";
    this->nbHeure = 0;
}

EcueControleur::EcueControleur(std::string nom, int nbHeure, GroupeEtudiant etudiants, Enseignant enseignant)
{
    this->nom = nom;
    this->nbHeure = nbHeure;
    this->etudiants = etudiants;
    this->enseignant = enseignant;
}



std::vector<GroupeEtudiant> EcueControleur::lireGroupesEtudiantCSV(QString& cheminFichier){
    std::vector<GroupeEtudiant> groupes;

    QFile file(QDir::currentPath() + "/../../CSV/" + cheminFichier );
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Impossible d'ouvrir le fichier" << std::endl;
        return groupes;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        if (fields.size() > 0) {
            GroupeEtudiant groupe(fields[0].toStdString());
            groupes.push_back(groupe);
        }
    }
    file.close();
    return groupes;
}



std::vector<Salle> EcueControleur::lireSallesCSV(QString& cheminFichier) {
    std::vector<Salle> salles;

    QFile file(QDir::currentPath() + "/../../CSV/" + cheminFichier);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Impossible d'ouvrir le fichier " << cheminFichier.toStdString() << std::endl;
        return salles;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        if (fields.size() > 1) {
            int numero = fields[0].toInt();
            QString typeSalleStr = fields[1].trimmed();

            cours typeSalle;
            if (typeSalleStr == "CM") {
                typeSalle = CM;
            } else if (typeSalleStr == "TD") {
                typeSalle = TD;
            } else if (typeSalleStr == "TP_INFO") {
                typeSalle = TP_INFO;
            } else if (typeSalleStr == "TP_ELEC") {
                typeSalle = TP_ELEC;
            } else if (typeSalleStr == "EXAMEN") {
                typeSalle = EXAMEN;
            } else {
                continue;
            }

            salles.push_back(Salle(numero, typeSalle));
        }
    }

    file.close();
    return salles;
}




std::vector<Enseignant> EcueControleur::lireEnseignantCSV(QString& cheminFichier) {
    std::vector<Enseignant> enseignants;

    // Ouvre le fichier CSV
    QFile file(QDir::currentPath() + "/../../CSV/" + cheminFichier);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Impossible d'ouvrir le fichier " << cheminFichier.toStdString() << std::endl;
        return enseignants;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        if (fields.size() > 1) {
            std::string nom = fields[0].toStdString();
            std::string prenom = fields[1].toStdString();

            enseignants.push_back(Enseignant(nom, prenom));
        }
    }

    file.close();
    return enseignants;
}


boolean EcueControleur::ajouterEnseignantCSV(const std::string& nom, const std::string& prenom) {
    QString fichier = "Enseignants.csv";
    std::vector<Enseignant> enseignants = lireEnseignantCSV(fichier);
    for (const Enseignant& enseignant : enseignants) {
        if (enseignant.getNom() == nom && enseignant.getPrenom() == prenom) {
            this->enseignant = enseignant;
            return TRUE;
        }
    }
    return FALSE;
}


boolean EcueControleur::ajouterSalleCSV(int numero, const cours typeSalle) {
    QString fichier = "Salles.csv";
    std::vector<Salle> salles = lireSallesCSV(fichier);
    for (const Salle& salle : salles) {
        if (salle.getNumero() == numero && salle.getTypeSalle() == typeSalle) {
            this->typeSalle = salle.getTypeSalle();
            return TRUE;
        }
    }
    return FALSE;
}


boolean EcueControleur::ajouterGroupeCSV(const std::string& groupe) {
    QString fichier = "Groupes.csv";
    std::vector<GroupeEtudiant> groupes = lireGroupesEtudiantCSV(fichier);
    for (const GroupeEtudiant& grp : groupes) {
        if (grp.getnomGroupe() == groupe) {
            this->etudiants = grp;
            return TRUE;
        }
    }
    return FALSE;
}



void EcueControleur::creerECUE(const std::string& nomECUE, const std::string& nom, const std::string& prenom, int numero, const std::vector<cours>& typesCours, const std::vector<int>& heuresParCours, const std::string& groupe) {
    if (typesCours.size() != heuresParCours.size()) {
        std::cerr << "Erreur : Le nombre de types de cours et le nombre d'heures ne correspondent pas." << std::endl;
        return;
    }

    this->nom = nomECUE;
    this->typesCours = typesCours;
    this->heuresParCours = heuresParCours;

    if (!ajouterEnseignantCSV(nom, prenom)) {
        std::cerr << "Erreur : Enseignant introuvable dans le fichier enseignant.csv." << std::endl;
        return;
    }

    if (!ajouterSalleCSV(numero, typesCours[0])) { // Vérification avec le premier type seulement
        std::cerr << "Erreur : Salle introuvable dans le fichier salles.csv." << std::endl;
        return;
    }

    if (!ajouterGroupeCSV(groupe)) {
        std::cerr << "Erreur : Groupe d'étudiants introuvable dans le fichier groupes.csv." << std::endl;
        return;
    }

    QString fichier = QDir::currentPath() + "/../../csv/ecue.csv";
    QFile file(fichier);
    bool fileExists = file.exists();

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        std::cerr << "Erreur : Impossible d'ouvrir ou de creer le fichier ecue.csv." << std::endl;
        return;
    }

    QTextStream out(&file);

    // En-tête si fichier n'existait pas
    if (!fileExists) {
        out << "NomECUE,Enseignant,Groupe,TypesCours,HeuresCours\n";
    }

    // Construction des listes pour types de cours et heures
    QStringList typesCoursStrList;
    QStringList heuresCoursStrList;
    for (size_t i = 0; i < typesCours.size(); ++i) {
        switch (typesCours[i]) {
        case CM: typesCoursStrList << "CM"; break;
        case TD: typesCoursStrList << "TD"; break;
        case TP_INFO: typesCoursStrList << "TP_INFO"; break;
        case TP_ELEC: typesCoursStrList << "TP_ELEC"; break;
        case EXAMEN: typesCoursStrList << "EXAMEN"; break;
        default: break;
        }
        heuresCoursStrList << QString::number(heuresParCours[i]);
    }

    QString typesCoursStr = typesCoursStrList.join("/");
    QString heuresCoursStr = heuresCoursStrList.join("/");

    QString enseignant = QString::fromStdString(nom + "," + prenom);
    QString groupeStr = QString::fromStdString(groupe);

    // Fichier CSV + 1 ligne
    out << QString::fromStdString(nomECUE) << ","
        << enseignant << ","
        << groupeStr << ","
        << typesCoursStr << ","
        << heuresCoursStr << "\n";

    file.close();

    std::cout << "ECUE creee : " << nomECUE << std::endl;
    std::cout << "Enseignant : " << nom << " " << prenom << std::endl;
    std::cout << "Types de cours : " << typesCoursStr.toStdString() << std::endl;
    std::cout << "Heures de cours : " << heuresCoursStr.toStdString() << std::endl;
    std::cout << "Groupe : " << groupe << std::endl;
}


int EcueControleur::getNombreHeure(const cours& typeCours) const {
    for (size_t i = 0; i < typesCours.size(); ++i) {
        if (typesCours[i] == typeCours) {
            return heuresParCours[i];
        }
    }
    return 0;
}




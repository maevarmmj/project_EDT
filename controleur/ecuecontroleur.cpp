#include "ecuecontroleur.h"

EcueControleur::EcueControleur() : etudiants(), enseignant() {
    this->nom = "";
    this->nbHeuresTotales = 0;
    this->nbHeuresTotalesAPlacer = 0;
    this->typesCours = {};
    this->heuresParCours = {};
    this->heuresAPlacer = {};
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


void EcueControleur::creerECUE(const std::string& nomECUE, const std::string& nom, const std::string& prenom, const std::vector<cours>& typesCours, const std::vector<int>& heuresParCours, const std::string& groupe) {
    if (typesCours.size() != heuresParCours.size()) {
        std::cerr << "Erreur : Le nombre de types de cours et le nombre d'heures ne correspondent pas." << std::endl;
        return;
    }

    // Chemin vers le fichier CSV
    QString fichier = QDir::currentPath() + "/../../CSV/Ecue.csv";
    QFile file(fichier);

    // Vérifier si le fichier existe et lire son contenu pour vérifier les doublons
    if (file.exists()) {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            std::cerr << "Erreur : Impossible de lire le fichier Ecue.csv." << std::endl;
            return;
        }

        QTextStream in(&file);
        bool isFirstLine = true;
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();

            // Ignorer la première ligne (en-têtes)
            if (isFirstLine) {
                isFirstLine = false;
                continue;
            }

            // Découper la ligne en colonnes
            QStringList fields = line.split(",");
            if (fields.size() >= 6) {
                QString existingNomECUE = fields[0];
                QString existingEnseignantNom = fields[1];
                QString existingEnseignantPrenom = fields[2];
                QString existingGroupe = fields[3];
                QString existingTypesCours = fields[4];

                // Construire les types de cours à comparer
                QStringList typesCoursStrList;
                for (size_t i = 0; i < typesCours.size(); ++i) {
                    switch (typesCours[i]) {
                    case CM: typesCoursStrList << "CM"; break;
                    case TD: typesCoursStrList << "TD"; break;
                    case TP_INFO: typesCoursStrList << "TP_INFO"; break;
                    case TP_ELEC: typesCoursStrList << "TP_ELEC"; break;
                    case EXAMEN: typesCoursStrList << "EXAMEN"; break;
                    default: break;
                    }
                }
                QString typesCoursStr = typesCoursStrList.join("/");

                // Vérifier si les informations correspondent
                if (existingNomECUE == QString::fromStdString(nomECUE) &&
                    existingEnseignantNom == QString::fromStdString(nom) &&
                    existingEnseignantPrenom == QString::fromStdString(prenom) &&
                    existingGroupe == QString::fromStdString(groupe) &&
                    existingTypesCours == typesCoursStr) {
                    std::cerr << "Erreur : Cette ECUE existe deja." << std::endl;
                    file.close();
                    return;
                }
            }
        }
        file.close();
    }

    // Ouvrir le fichier en mode ajout
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        std::cerr << "Erreur : Impossible d'ouvrir ou de créer le fichier Ecue.csv." << std::endl;
        return;
    }

    QTextStream out(&file);
    bool fileExists = file.exists();

    if (!fileExists) {
        out << "NomECUE,NomEnseignant,PrenomEnseignant,Groupe,TypesCours,HeuresCours,HeuresAPlacer\n";
    }

    QStringList typesCoursStrList;
    QStringList heuresCoursStrList;
    QStringList heuresRestantesCoursStrList;

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
        heuresRestantesCoursStrList << QString::number(heuresParCours[i]);
    }

    QString typesCoursStr = typesCoursStrList.join("/");
    QString heuresCoursStr = heuresCoursStrList.join("/");
    QString heuresRestantesCoursStr = heuresRestantesCoursStrList.join("/");

    QString enseignant = QString::fromStdString(nom + "," + prenom);
    QString groupeStr = QString::fromStdString(groupe);

    out << QString::fromStdString(nomECUE) << ","
        << enseignant << ","
        << groupeStr << ","
        << typesCoursStr << ","
        << heuresCoursStr << ","
        << heuresRestantesCoursStr << "\n";

    file.close();

    std::cout << "ECUE créée : " << nomECUE << std::endl;
    std::cout << "Enseignant : " << nom << " " << prenom << std::endl;
    std::cout << "Types de cours : " << typesCoursStr.toStdString() << std::endl;
    std::cout << "Heures de cours : " << heuresCoursStr.toStdString() << std::endl;
    std::cout << "Heures restantes : " << heuresRestantesCoursStr.toStdString() << std::endl;
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

uint32 EcueControleur::decrementerHeuresCours(const cours& typeCours, uint32 nbHeuresADecrementer) {
    for (size_t i = 0; i < typesCours.size(); ++i) {
        if (typesCours[i] == typeCours) {
            heuresAPlacer[i] -= nbHeuresADecrementer;
            if (heuresAPlacer[i] < 0) {
                heuresAPlacer[i] = 0;
            }

            QString fichier = QDir::currentPath() + "/../../CSV/Ecue.csv";
            QFile file(fichier);

            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                std::cerr << "Erreur : Impossible d'ouvrir le fichier Ecue.csv." << std::endl;
                return heuresAPlacer[i];
            }

            QTextStream in(&file);
            QStringList lignes;
            bool modifie = false;

            while (!in.atEnd()) {
                QString ligne = in.readLine();
                QStringList data = ligne.split(",");

                if (data.size() >= 7) {
                    QString existingNomECUE = data[0].trimmed();
                    QStringList existingTypesCours = data[4].split("/");
                    QStringList existingHeuresRestantesCours = data[6].split("/");

                    if (existingNomECUE == QString::fromStdString(this->nom)) {
                        for (int j = 0; j < existingTypesCours.size(); ++j) {
                            if (existingTypesCours[j] == QString::fromStdString(coursToString(typeCours))) {
                                existingHeuresRestantesCours[j] = QString::number(heuresAPlacer[i]);
                                modifie = true;
                                break;
                            }
                        }
                        data[6] = existingHeuresRestantesCours.join("/"); // Met à jour la 7e colonne
                        ligne = data.join(",");
                    }
                }

                lignes.append(ligne);
            }

            file.close();

            if (modifie) {
                if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
                    std::cerr << "Erreur : Impossible de reecrire le fichier Ecue.csv." << std::endl;
                    return heuresAPlacer[i];
                }

                QTextStream out(&file);
                for (const QString& ligne : lignes) {
                    out << ligne << "\n";
                }

                file.close();
                std::cout << "MAJ reussie du fichier Ecue.csv pour le type de cours "
                          << coursToString(typeCours) << " avec " << heuresAPlacer[i] << " heures restantes." << std::endl;
            } else {
                std::cerr << "Erreur : Aucune modification dans le fichier Ecue.csv." << std::endl;
            }

            return heuresAPlacer[i];
        }
    }

    std::cerr << "Erreur : Type de cours introuvable" << std::endl;
    return 0;
}



std::string EcueControleur::coursToString(const cours& typeCours) const {
    switch (typeCours) {
    case CM: return "CM";
    case TD: return "TD";
    case TP_INFO: return "TP_INFO";
    case TP_ELEC: return "TP_ELEC";
    case EXAMEN: return "EXAMEN";
    default: return "";
    }
}


uint32 EcueControleur::getNombreHeureTotalAPlacer() {
    for (size_t i = 0; i < heuresAPlacer.size(); ++i) {
        nbHeuresTotalesAPlacer += heuresAPlacer[i];
    }
    return nbHeuresTotalesAPlacer;
}


uint32 EcueControleur::getNombreHeureTotal() {

    for (size_t i = 0; i < heuresParCours.size(); ++i) {
        this->nbHeuresTotales += heuresParCours[i];
    }

    return nbHeuresTotales;
}




bool EcueControleur::retirerECUECSV(const std::string& nomECUE, const std::string& nom, const std::string& prenom, const std::string& groupe) {
    QString csv = QDir::currentPath() + QString::fromStdString("/../../CSV/Ecue.csv");
    QFile file(csv);

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Erreur : impossible d'ouvrir le fichier:" << file.errorString();
        return false;
    }

    QTextStream in(&file);
    QStringList lines;
    bool found = false;
    bool isFirstLine = true;

    QString line;
    while (in.readLineInto(&line)) {
        if (isFirstLine) {
            isFirstLine = false;
            lines.append(line);
            continue;
        }

        QStringList data = line.split(",");
        if (!data.isEmpty() && data.size() > 1) {
            QString existingNomECUE = data.first().trimmed();
            QString existingNomEnseignant = data.at(1).trimmed();
            QString existingPrenomEnseignant = data.at(2).trimmed();
            QString existingGroupeEtudiant = data.at(3).trimmed();


            if (existingNomECUE == QString::fromStdString(nomECUE).trimmed() &&
                existingNomEnseignant == QString::fromStdString(nom).trimmed() &&
                existingPrenomEnseignant == QString::fromStdString(prenom).trimmed() &&
                existingGroupeEtudiant == QString::fromStdString(groupe).trimmed()) {
                found = true;
                continue;
            }
        }

        lines.append(line);
    }

    if (!found) {
        qDebug() << "Erreur : ECUE " << QString::fromStdString(nom)
        << " " << QString::fromStdString(nomECUE)
        << " non trouvé dans le fichier CSV.";
        file.close();
        return false;
    }

    file.seek(0);
    file.resize(0);

    QTextStream out(&file);
    for (const QString& updatedLine : lines) {
        out << updatedLine << "\n";
    }

    file.close();
    return true;
}



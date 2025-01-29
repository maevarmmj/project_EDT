#include "enseignantControl.h"


CreationResult ajouterEnseignantCSV(const std::string& nom, const std::string& prenom){
    QString csvDirPath = QDir::currentPath() + "/../../CSV";
    QDir csvDir(csvDirPath);

    if (!csvDir.exists()) {
        if (!csvDir.mkpath(".")) {
            qDebug() << "Erreur : impossible de créer le dossier CSV:" << csvDir.path();
            return CreationResult::Error;
        }
    }

    QString csv = QDir::currentPath() + QString::fromStdString("/../../CSV/Enseignants.csv");
    QFile file(csv);
    bool fileExists = file.exists();


    if (fileExists) {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Erreur : le fichier ne peut pas s'ouvrir" << file.errorString();
            return CreationResult::Error;
        }
        QTextStream in(&file);
        QString line;
        while (in.readLineInto(&line)) {
            QStringList existingData = line.split(",");
            if (!existingData.isEmpty() && existingData.size() > 1 && existingData.first() == QString::fromStdString(nom) && existingData.at(1) == QString::fromStdString(prenom)) {
                qDebug() << "Erreur : l'enseignant " << QString::fromStdString(nom) << " " << QString::fromStdString(prenom) << " existe déjà dans le CSV";
                file.close();
                return CreationResult::AlreadyExists;
            }
        }
        file.close();
    }

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text | (fileExists ? QIODevice::Append : QIODevice::Truncate))) {
        qDebug() << "Erreur : le fichier ne s'ouvre pas:" << file.errorString();
    }
    QTextStream out(&file);
    if (!fileExists) {
        out << "Nom,Prenom" << "\n";
    }
    out << QString::fromStdString(nom) << "," << QString::fromStdString(prenom) << "\n";

    file.close();
    return CreationResult::Success;
}


SuppressionResult retirerEnseignantCSV(const std::string& nom, const std::string& prenom) {
    QString csvEnseignants = QDir::currentPath() + QString::fromStdString("/../../CSV/Enseignants.csv");
    QFile fileEnseignants(csvEnseignants);

    if (!fileEnseignants.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Erreur : impossible d'ouvrir le fichier:" << fileEnseignants.errorString();
        return SuppressionResult::Error;
    }

    QTextStream inEnseignants(&fileEnseignants);
    QStringList linesEnseignants;
    bool found = false;
    bool isFirstLine = true;

    QString line;
    while (inEnseignants.readLineInto(&line)) {
        if (isFirstLine) {
            isFirstLine = false;
            linesEnseignants.append(line);
            continue;
        }

        QStringList data = line.split(",");
        if (!data.isEmpty() && data.size() > 1) {
            QString existingNom = data.first().trimmed();
            QString existingPrenom = data.at(1).trimmed();

            if (existingNom == QString::fromStdString(nom).trimmed() &&
                existingPrenom == QString::fromStdString(prenom).trimmed()) {
                found = true;
                continue;  // Ne pas réécrire cette ligne (supprime l'enseignant)
            }
        }

        linesEnseignants.append(line);
    }

    if (!found) {
        qDebug() << "Erreur : Enseignant " << QString::fromStdString(nom)
        << " " << QString::fromStdString(prenom)
        << " non trouvé dans le fichier CSV.";
        fileEnseignants.close();
        return SuppressionResult::Error;
    }

    // Réécrire le fichier Enseignants.csv sans l'enseignant supprimé
    fileEnseignants.seek(0);
    fileEnseignants.resize(0);

    QTextStream outEnseignants(&fileEnseignants);
    for (const QString& updatedLine : linesEnseignants) {
        outEnseignants << updatedLine << "\n";
    }

    fileEnseignants.close();

    // Supprimer les lignes associées dans Ecue.csv
    QString csvEcue = QDir::currentPath() + QString::fromStdString("/../../CSV/Ecue.csv");
    QFile fileEcue(csvEcue);

    if (!fileEcue.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Erreur : impossible d'ouvrir le fichier:" << fileEcue.errorString();
        return SuppressionResult::Error;
    }

    QTextStream inEcue(&fileEcue);
    QStringList linesEcue;
    isFirstLine = true;
    found = false;  // Réinitialiser le flag pour Ecue.csv

    while (inEcue.readLineInto(&line)) {
        if (isFirstLine) {
            isFirstLine = false;
            linesEcue.append(line);
            continue;
        }

        QStringList data = line.split(",");
        if (!data.isEmpty() && data.size() > 3) {
            QString existingNom = data.at(1).trimmed();  // Nom enseignant (2e colonne)
            QString existingPrenom = data.at(2).trimmed();  // Prénom enseignant (3e colonne)

            if (existingNom == QString::fromStdString(nom).trimmed() &&
                existingPrenom == QString::fromStdString(prenom).trimmed()) {
                found = true;
                continue;  // Ne pas réécrire cette ligne (supprime les ECUE associées)
            }
        }

        linesEcue.append(line);
    }

    // Réécrire le fichier Ecue.csv sans les lignes associées à l'enseignant
    fileEcue.seek(0);
    fileEcue.resize(0);

    QTextStream outEcue(&fileEcue);
    for (const QString& updatedLine : linesEcue) {
        outEcue << updatedLine << "\n";
    }

    fileEcue.close();

    if (!found) {
        qDebug() << "Aucune ECUE associée à l'enseignant " << QString::fromStdString(nom)
                 << " " << QString::fromStdString(prenom) << " trouvée dans le fichier Ecue.csv.";
    } else {
        qDebug() << "Toutes les ECUE associées à l'enseignant " << QString::fromStdString(nom)
                 << " " << QString::fromStdString(prenom) << " ont été supprimées.";
    }

    // supprimer de la base de données
    deleteReservationsByTeacher(QString::fromStdString(nom), QString::fromStdString(prenom));

    return SuppressionResult::Success;
}

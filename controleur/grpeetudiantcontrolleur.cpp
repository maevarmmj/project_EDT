#include "grpeetudiantcontrolleur.h"


CreationResult ajouterGroupeEtudiantCSV(const std::string& nomGroupe){
    QString csvDirPath = QDir::currentPath() + "/../../CSV";
    QDir csvDir(csvDirPath);

    if (!csvDir.exists()) {
        if (!csvDir.mkpath(".")) {
            qDebug() << "Erreur : impossible de créer le dossier CSV:" << csvDir.path();
            return CreationResult::Error;
        }
    }

    QString csv = QDir::currentPath() + QString::fromStdString("/../../CSV/Groupes.csv");
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
            if (!existingData.isEmpty() && existingData.first() == QString::fromStdString(nomGroupe)) {
                qDebug() << "Erreur : le groupe " << QString::fromStdString(nomGroupe) << " " << " existe déjà dans le CSV";
                file.close();
                return CreationResult::AlreadyExists;
            }
        }
        file.close();
    }

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text | (fileExists ? QIODevice::Append : QIODevice::Truncate))) {
        qDebug() << "Erreur : le fichier ne s'ouvre pas:" << file.errorString();
        return CreationResult::Error;
    }
    QTextStream out(&file);
    if (!fileExists) {
        out << "Groupe" << "\n";
    }
    out << QString::fromStdString(nomGroupe) << "\n";

    file.close();
    return CreationResult::Success;
}


SuppressionResult retirerGroupeEtudiantCSV(const std::string& nomGroupe) {
    // Fichier Groupes.csv
    QString csvGroupes = QDir::currentPath() + QString::fromStdString("/../../CSV/Groupes.csv");
    QFile fileGroupes(csvGroupes);

    if (!fileGroupes.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Erreur : impossible d'ouvrir le fichier:" << fileGroupes.errorString();
        return SuppressionResult::Error;
    }

    QTextStream inGroupes(&fileGroupes);
    QStringList linesGroupes;
    bool found = false;
    bool isFirstLine = true;

    QString line;
    while (inGroupes.readLineInto(&line)) {
        if (isFirstLine) {
            isFirstLine = false;
            linesGroupes.append(line);
            continue;
        }

        QStringList data = line.split(",");
        if (!data.isEmpty() && data.first().trimmed() == QString::fromStdString(nomGroupe).trimmed()) {
            found = true;
            continue;  // Ne pas réécrire cette ligne (supprime le groupe)
        }

        linesGroupes.append(line);
    }

    if (!found) {
        qDebug() << "Erreur : Groupe " << QString::fromStdString(nomGroupe) << " non trouvé dans le fichier CSV.";
        fileGroupes.close();
        return SuppressionResult::Error;
    }

    // Réécrire le fichier Groupes.csv sans le groupe supprimé
    fileGroupes.seek(0);
    fileGroupes.resize(0);

    QTextStream outGroupes(&fileGroupes);
    for (const QString& updatedLine : linesGroupes) {
        outGroupes << updatedLine << "\n";
    }

    fileGroupes.close();

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
            QString existingGroupe = data.at(3).trimmed();  // 4e colonne (groupe)

            if (existingGroupe == QString::fromStdString(nomGroupe).trimmed()) {
                found = true;
                continue;  // Ne pas réécrire cette ligne (supprime les ECUE associées)
            }
        }

        linesEcue.append(line);
    }

    // Réécrire le fichier Ecue.csv sans les lignes associées au groupe
    fileEcue.seek(0);
    fileEcue.resize(0);

    QTextStream outEcue(&fileEcue);
    for (const QString& updatedLine : linesEcue) {
        outEcue << updatedLine << "\n";
    }

    fileEcue.close();

    if (!found) {
        qDebug() << "Aucune ECUE associée au groupe " << QString::fromStdString(nomGroupe) << " trouvée dans le fichier Ecue.csv.";
    } else {
        qDebug() << "Toutes les ECUE associées au groupe " << QString::fromStdString(nomGroupe) << " ont été supprimées.";
    }

    deleteReservationsByGroup(QString::fromStdString(nomGroupe));

    return SuppressionResult::Success;
}

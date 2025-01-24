#include "enseignantControl.h"


bool ajouterEnseignantCSV(const std::string& nom, const std::string& prenom){
    QString csv = QDir::currentPath() + QString::fromStdString("/../../CSV/Enseignants.csv");
    QFile file(csv);
    bool fileExists = file.exists();


    if (fileExists) {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Erreur : le fichier ne peut pas s'ouvrir" << file.errorString();
            return false;
        }
        QTextStream in(&file);
        QString line;
        while (in.readLineInto(&line)) {
            QStringList existingData = line.split(",");
            if (!existingData.isEmpty() && existingData.size() > 1 && existingData.first() == QString::fromStdString(nom) && existingData.at(1) == QString::fromStdString(prenom)) {
                qDebug() << "Erreur : l'enseignant " << QString::fromStdString(nom) << " " << QString::fromStdString(prenom) << " existe déjà dans le CSV";
                file.close();
                return false;
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
    return true;
}


bool retirerEnseignantCSV(const std::string& nom, const std::string& prenom) {
    QString csv = QDir::currentPath() + QString::fromStdString("/../../CSV/Enseignants.csv");
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
            QString existingNom = data.first().trimmed();
            QString existingPrenom = data.at(1).trimmed();

            if (existingNom == QString::fromStdString(nom).trimmed() &&
                existingPrenom == QString::fromStdString(prenom).trimmed()) {
                found = true;
                continue;
            }
        }

        lines.append(line);
    }

    if (!found) {
        qDebug() << "Erreur : Enseignant " << QString::fromStdString(nom)
        << " " << QString::fromStdString(prenom)
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

#include "grpeetudiantcontrolleur.h"


bool ajouterGroupeEtudiantCSV(const std::string& nomGroupe){
    QString csv = QDir::currentPath() + QString::fromStdString("/../../CSV/Groupes.csv");
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
            if (!existingData.isEmpty() && existingData.first() == QString::fromStdString(nomGroupe)) {
                qDebug() << "Erreur : le groupe " << QString::fromStdString(nomGroupe) << " " << " existe déjà dans le CSV";
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
        out << "Groupe" << "\n";
    }
    out << QString::fromStdString(nomGroupe) << "\n";

    file.close();
    return true;
}


bool retirerGroupeEtudiantCSV(const std::string& nomGroupe) {
    QString csv = QDir::currentPath() + QString::fromStdString("/../../CSV/Groupes.csv");
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
        if (!data.isEmpty() && data.first() == QString::fromStdString(nomGroupe)){
                found = true;
                continue;
            }


        lines.append(line);
    }

    if (!found) {
        qDebug() << "Erreur : Groupe " << QString::fromStdString(nomGroupe) << " non trouvé dans le fichier CSV";
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

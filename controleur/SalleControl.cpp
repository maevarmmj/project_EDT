#include "SalleControl.h"

QString csv = QDir::currentPath() + QString::fromStdString("/../../CSV/Salles.csv");

QString getCoursName(cours cours) {
    switch (cours) {
    case CM:
        return "CM";
    case TD:
        return "TD";
    case TP_INFO:
        return "TP_INFO";
    case TP_ELEC:
        return "TP_ELEC";
    case EXAMEN:
        return "EXAMEN";
    default:
        return "";
    }
}

CreationResult ajouterSalleCSV(int numero, cours type) {
    QString csvDirPath = QDir::currentPath() + "/../../CSV";
    QDir csvDir(csvDirPath);

    if (!csvDir.exists()) {
        if (!csvDir.mkpath(".")) {
            qDebug() << "Erreur : impossible de créer le dossier CSV:" << csvDir.path();
            return CreationResult::Error;
        }
    }

    QString csv = QDir::currentPath() + QString::fromStdString("/../../CSV/Salles.csv");
    QFile file(csv);
    bool fileExists = file.exists();

    QList<QPair<int, QString>> salles; // Pour stocker les salles existantes et la nouvelle

    if (fileExists) {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Error opening file for duplicate check:" << file.errorString();
            return CreationResult::Error;
        }

        QTextStream in(&file);
        QString line;
        bool firstLine = true;
        while (in.readLineInto(&line)) {
            if (firstLine){
                firstLine = false;
                continue;
            }
            QStringList existingData = line.split(",");
            if (!existingData.isEmpty() && existingData.size() > 1 ) {
                if (existingData.first().toInt() == numero ) {
                    qDebug() << "Error: Numero" << QString::number(numero) << "already exists in the CSV file.";
                    file.close();
                    return CreationResult::AlreadyExists;
                }
                salles.append(qMakePair(existingData.first().toInt(), existingData.at(1)));
            }
        }
        file.close();
    }

    salles.append(qMakePair(numero, QString::fromStdString(CoursToStr(type))));
    std::sort(salles.begin(), salles.end(), [](const QPair<int, QString>& a, const QPair<int, QString>& b) {
        return a.first < b.first; // Comparaison numérique
    });


    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error opening file:" << file.errorString();
        return CreationResult::Error;
    }
    QTextStream out(&file);
    out << "Numero,Type" << "\n";


    for(const auto& salle : salles) {
        out << salle.first << "," << salle.second << "\n";
    }

    file.close();
    return CreationResult::Success;
}


SuppressionResult retirerSalleCSV(int numero){
    cours typeCours;
    QFile file(csv);

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Error opening file:" << file.errorString();
        return SuppressionResult::Error;
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
        if (!data.isEmpty() && data.first() == QString::number(numero)) {
            found = true;
            typeCours = StrToCours(data[1].toStdString());
            continue;
        }
        lines.append(line);
    }

    if (!found) {
        qDebug() << "Error: Numero" << QString::number(numero) << "not found in CSV.";
        file.close();
        return SuppressionResult::Error;
    }

    file.seek(0);
    file.resize(0);

    QTextStream out(&file);
    for (const QString& updatedLine : lines) {
        out << updatedLine << "\n";
    }

    file.close();

    deleteReservationsBySalle(numero, typeCours);

    return SuppressionResult::Success;
}

// Function to read room numbers from the CSV file
QList<int> readRoomNumbersFromCSV(const QString& typeCours) {
    QList<int> roomNumbers;
    QFile file(csv);


    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error: Could not open CSV file:" << file.errorString();
        return roomNumbers;
    }

    QTextStream in(&file);
    in.readLine(); // Skip header line (Numero,Cours)

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        if (fields.size() >= 2) { // Ensure we have at least Numero and Cours
            bool ok;
            int roomNumber = fields[0].toInt(&ok);
            QString cours = fields[1];
            if (ok && cours == typeCours) { // Check if course type matches
                roomNumbers.append(roomNumber);
            }
        }
    }

    file.close();
    return roomNumbers;
}

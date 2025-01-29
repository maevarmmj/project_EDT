#import "SalleControl.h"

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

CreationResult ajouterSalleCSV(int numero, cours cours){
    QString csvDirPath = QDir::currentPath() + "/../../CSV";
    QDir csvDir(csvDirPath);

    if (!csvDir.exists()) {
        if (!csvDir.mkpath(".")) {
            qDebug() << "Erreur : impossible de créer le dossier CSV:" << csvDir.path();
            return CreationResult::Error;
        }
    }

    QFile file(csv);
    bool fileExists = file.exists();


    if (fileExists) {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Error opening file for duplicate check:" << file.errorString();
            return CreationResult::Error;
        }
        QTextStream in(&file);
        QString line;
        while (in.readLineInto(&line)) {
            QStringList existingData = line.split(",");
            if (!existingData.isEmpty() && existingData.first() == QString::number(numero)) {
                qDebug() << "Error: Numero" << QString::number(numero) << "already exists in the CSV file.";
                file.close();
                return CreationResult::AlreadyExists;
            }
        }
        file.close();
    }

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text | (fileExists ? QIODevice::Append : QIODevice::Truncate))) {
        qDebug() << "Error opening file:" << file.errorString();
    }
    QTextStream out(&file);
    if (!fileExists) {
        out << "Numero,Cours" << "\n";
    }
    out << numero << "," << getCoursName(cours) << "\n";

    file.close();
    return CreationResult::Success;
}


bool retirerSalleCSV(int numero){
    cours typeCours;
    QFile file(csv);

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Error opening file:" << file.errorString();
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
        return false;
    }

    file.seek(0);
    file.resize(0);

    QTextStream out(&file);
    for (const QString& updatedLine : lines) {
        out << updatedLine << "\n";
    }

    file.close();

    deleteReservationsBySalle(numero, typeCours);

    return true;
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

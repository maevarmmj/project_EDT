#import "SalleControl.h"

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

bool ajouterSalleCSV(int numero, cours cours){
    QString csv = QDir::currentPath() + QString::fromStdString("/../../CSV/Salles.csv");
    QFile file(csv);
    bool fileExists = file.exists();


    if (fileExists) {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Error opening file for duplicate check:" << file.errorString();
            return false;
        }
        QTextStream in(&file);
        QString line;
        while (in.readLineInto(&line)) {
            QStringList existingData = line.split(",");
            if (!existingData.isEmpty() && existingData.first() == QString::number(numero)) {
                qDebug() << "Error: Numero" << QString::number(numero) << "already exists in the CSV file.";
                file.close();
                return false;
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
    return true;
}


bool retirerSalleCSV(int numero){
    QString csv = QDir::currentPath() + QString::fromStdString("/../../CSV/Salles.csv");
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
    return true;
}

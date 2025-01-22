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

bool addSalleCSV(int numero, cours cours){
    QString csv = QDir::currentPath() + QString::fromStdString("/../../CSV/Salle.csv");
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

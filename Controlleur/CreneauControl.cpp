#include "CreneauControl.h"

tm setJourHeure(int jourSemaine, int heure){
    tm jourHeure;
    jourHeure.tm_wday = jourSemaine;
    jourHeure.tm_hour = heure;
    return jourHeure;
}

int salleLibreHeure(int heure){
    QFile file(QDir::currentPath() + QString::fromStdString("/../../salles.csv") );

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Error: Could not open file " << std::endl;
    }

    QTextStream in(&file);
    while (!in.atEnd()){
        QString line = in.readLine();
        QStringList liste = line.split(",");
        std::cout << liste[0].toStdString() << std::endl;
    }
    return 1;
}

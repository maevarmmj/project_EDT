#include "main.h"
#include <iostream>

void afficherQMap(const QMap<QString, QVariant>& map) {
    QString output;
    QMapIterator<QString, QVariant> i(map);
    while (i.hasNext()) {
        i.next();
        // Formater chaque paire clé/valeur
        output += i.key() + ": " + i.value().toString();

        // Ajouter une virgule et un espace si ce n'est pas la dernière paire
        if (i.hasNext()) {
            output += ", ";
        }
    }
    qDebug() << output;
}

void creerReservation(){
    // Semaine 1
    // Lundi
    insertReservation(101, "Analyse de Données", "Dupont", "Jean", "E2", "CM", "20/10", "15/5", 1, "Mon 08:00", "Mon 09:00");
    insertReservation(201, "Algorithmique", "Martin", "Sophie", "E2", "TP", "25/15", "20/10", 1, "Mon 08:00", "Mon 09:00");
    insertReservation(301, "Bases de Données", "Lefevre", "Pierre", "E3", "TD", "20/10/5", "15/5/2", 1, "Mon 09:00", "Mon 10:00");
    insertReservation(102, "Réseaux", "Bertolim", "Maria", "E4", "CM", "15/10", "10/5", 1, "Mon 10:00", "Mon 11:00");
    insertReservation(202, "Systèmes d'Exploitation", "Garcia", "Carlos", "E4", "TP", "18/12", "12/8", 1, "Mon 10:00", "Mon 11:00");
    insertReservation(101, "Programmation Orientée Objet", "Moreau", "Isabelle", "E3", "CM", "30/20", "25/15", 1, "Mon 11:00", "Mon 12:00");
    insertReservation(302, "Intelligence Artificielle", "Durand", "Michel", "E4", "TD", "22/11", "18/8", 1, "Mon 11:00", "Mon 12:00");
    insertReservation(201, "Compilation", "Dupont", "Jean", "E4", "TP", "15/10", "10/7", 1, "Mon 13:00", "Mon 14:00");
    insertReservation(102, "Théorie des Langages", "Martin", "Sophie", "E2", "CM", "16/8", "12/4", 1, "Mon 14:00", "Mon 15:00");
    insertReservation(301, "Sécurité Informatique", "Bertolim", "Maria", "E3", "TD", "14/7/2", "10/3/1", 1, "Mon 14:00", "Mon 15:00");

    // Mardi
    insertReservation(202, "Analyse de Données", "Dupont", "Jean", "E2", "TP", "20/10", "15/5", 1, "Tue 08:00", "Tue 09:00");
    insertReservation(101, "Algorithmique", "Martin", "Sophie", "E2", "CM", "25/15", "20/10", 1, "Tue 09:00", "Tue 10:00");
    insertReservation(302, "Bases de Données", "Lefevre", "Pierre", "E3", "TD", "20/10/5", "15/5/2", 1, "Tue 09:00", "Tue 10:00");
    insertReservation(201, "Réseaux", "Bertolim", "Maria", "E4", "TP", "15/10", "10/5", 1, "Tue 10:00", "Tue 11:00");
    insertReservation(102, "Systèmes d'Exploitation", "Garcia", "Carlos", "E4", "CM", "18/12", "12/8", 1, "Tue 11:00", "Tue 12:00");
    insertReservation(301, "Programmation Orientée Objet", "Moreau", "Isabelle", "E3", "TD", "30/20", "25/15", 1, "Tue 11:00", "Tue 12:00");
    insertReservation(101, "Intelligence Artificielle", "Durand", "Michel", "E4", "CM", "22/11", "18/8", 1, "Tue 13:00", "Tue 14:00");
    insertReservation(202, "Compilation", "Dupont", "Jean", "E4", "TP", "15/10", "10/7", 1, "Tue 14:00", "Tue 15:00");
    insertReservation(302, "Théorie des Langages", "Martin", "Sophie", "E2", "TD", "16/8", "12/4", 1, "Tue 14:00", "Tue 15:00");
    insertReservation(401, "Sécurité Informatique", "Bertolim", "Maria", "E3", "EXAMEN", "14/7/2", "10/3/1", 1, "Tue 15:00", "Tue 16:00");

    // Mercredi
    insertReservation(101, "Analyse de Données", "Dupont", "Jean", "E2", "CM", "20/10", "15/5", 1, "Wed 08:00", "Wed 09:00");
    insertReservation(201, "Algorithmique", "Martin", "Sophie", "E2", "TP", "25/15", "20/10", 1, "Wed 08:00", "Wed 09:00");
    insertReservation(301, "Bases de Données", "Lefevre", "Pierre", "E3", "TD", "20/10/5", "15/5/2", 1, "Wed 09:00", "Wed 10:00");
    insertReservation(102, "Réseaux", "Bertolim", "Maria", "E4", "CM", "15/10", "10/5", 1, "Wed 10:00", "Wed 11:00");
    insertReservation(202, "Systèmes d'Exploitation", "Garcia", "Carlos", "E4", "TP", "18/12", "12/8", 1, "Wed 10:00", "Wed 11:00");
    insertReservation(101, "Programmation Orientée Objet", "Moreau", "Isabelle", "E3", "CM", "30/20", "25/15", 1, "Wed 11:00", "Wed 12:00");
    insertReservation(302, "Intelligence Artificielle", "Durand", "Michel", "E4", "TD", "22/11", "18/8", 1, "Wed 11:00", "Wed 12:00");
    insertReservation(201, "Compilation", "Dupont", "Jean", "E4", "TP", "15/10", "10/7", 1, "Wed 13:00", "Wed 14:00");
    insertReservation(102, "Théorie des Langages", "Martin", "Sophie", "E2", "CM", "16/8", "12/4", 1, "Wed 14:00", "Wed 15:00");
    insertReservation(301, "Sécurité Informatique", "Bertolim", "Maria", "E3", "TD", "14/7/2", "10/3/1", 1, "Wed 14:00", "Wed 15:00");

    // Jeudi
    insertReservation(202, "Analyse de Données", "Dupont", "Jean", "E2", "TP", "20/10", "15/5", 1, "Thu 08:00", "Thu 09:00");
    insertReservation(101, "Algorithmique", "Martin", "Sophie", "E2", "CM", "25/15", "20/10", 1, "Thu 09:00", "Thu 10:00");
    insertReservation(302, "Bases de Données", "Lefevre", "Pierre", "E3", "TD", "20/10/5", "15/5/2", 1, "Thu 09:00", "Thu 10:00");
    insertReservation(201, "Réseaux", "Bertolim", "Maria", "E4", "TP", "15/10", "10/5", 1, "Thu 10:00", "Thu 11:00");
    insertReservation(102, "Systèmes d'Exploitation", "Garcia", "Carlos", "E4", "CM", "18/12", "12/8", 1, "Thu 11:00", "Thu 12:00");
    insertReservation(301, "Programmation Orientée Objet", "Moreau", "Isabelle", "E3", "TD", "30/20", "25/15", 1, "Thu 11:00", "Thu 12:00");
    insertReservation(101, "Intelligence Artificielle", "Durand", "Michel", "E4", "CM", "22/11", "18/8", 1, "Thu 13:00", "Thu 14:00");
    insertReservation(202, "Compilation", "Dupont", "Jean", "E4", "TP", "15/10", "10/7", 1, "Thu 14:00", "Thu 15:00");
    insertReservation(302, "Théorie des Langages", "Martin", "Sophie", "E2", "TD", "16/8", "12/4", 1, "Thu 14:00", "Thu 15:00");
    insertReservation(401, "Sécurité Informatique", "Bertolim", "Maria", "E3", "EXAMEN", "14/7/2", "10/3/1", 1, "Thu 15:00", "Thu 16:00");

    // Vendredi
    insertReservation(101, "Analyse de Données", "Dupont", "Jean", "E2", "CM", "20/10", "15/5", 1, "Fri 08:00", "Fri 09:00");
    insertReservation(201, "Algorithmique", "Martin", "Sophie", "E2", "TP", "25/15", "20/10", 1, "Fri 08:00", "Fri 09:00");
    insertReservation(301, "Bases de Données", "Lefevre", "Pierre", "E3", "TD", "20/10/5", "15/5/2", 1, "Fri 09:00", "Fri 10:00");
    insertReservation(102, "Réseaux", "Bertolim", "Maria", "E4", "CM", "15/10", "10/5", 1, "Fri 10:00", "Fri 11:00");
    insertReservation(202, "Systèmes d'Exploitation", "Garcia", "Carlos", "E4", "TP", "18/12", "12/8", 1, "Fri 10:00", "Fri 11:00");
    insertReservation(101, "Programmation Orientée Objet", "Moreau", "Isabelle", "E3", "CM", "30/20", "25/15", 1, "Fri 11:00", "Fri 12:00");
    insertReservation(302, "Intelligence Artificielle", "Durand", "Michel", "E4", "TD", "22/11", "18/8", 1, "Fri 11:00", "Fri 12:00");
    insertReservation(201, "Compilation", "Dupont", "Jean", "E4", "TP", "15/10", "10/7", 1, "Fri 13:00", "Fri 14:00");
    insertReservation(102, "Théorie des Langages", "Martin", "Sophie", "E2", "CM", "16/8", "12/4", 1, "Fri 14:00", "Fri 15:00");
    insertReservation(301, "Sécurité Informatique", "Bertolim", "Maria", "E3", "TD", "14/7/2", "10/3/1", 1, "Fri 14:00", "Fri 15:00");

    // Semaine 2
    // Lundi
    insertReservation(101, "Analyse de Données", "Dupont", "Jean", "E2", "CM", "20/10", "15/5", 2, "Mon 08:00", "Mon 09:00");
    insertReservation(201, "Algorithmique", "Martin", "Sophie", "E2", "TP", "25/15", "20/10", 2, "Mon 08:00", "Mon 09:00");
    insertReservation(301, "Bases de Données", "Lefevre", "Pierre", "E3", "TD", "20/10/5", "15/5/2", 2, "Mon 09:00", "Mon 10:00");
    insertReservation(102, "Réseaux", "Bertolim", "Maria", "E4", "CM", "15/10", "10/5", 2, "Mon 10:00", "Mon 11:00");
    insertReservation(202, "Systèmes d'Exploitation", "Garcia", "Carlos", "E4", "TP", "18/12", "12/8", 2, "Mon 10:00", "Mon 11:00");
    insertReservation(101, "Programmation Orientée Objet", "Moreau", "Isabelle", "E3", "CM", "30/20", "25/15", 2, "Mon 11:00", "Mon 12:00");
    insertReservation(302, "Intelligence Artificielle", "Durand", "Michel", "E4", "TD", "22/11", "18/8", 2, "Mon 11:00", "Mon 12:00");
    insertReservation(201, "Compilation", "Dupont", "Jean", "E4", "TP", "15/10", "10/7", 2, "Mon 13:00", "Mon 14:00");
    insertReservation(102, "Théorie des Langages", "Martin", "Sophie", "E2", "CM", "16/8", "12/4", 2, "Mon 14:00", "Mon 15:00");
    insertReservation(301, "Sécurité Informatique", "Bertolim", "Maria", "E3", "TD", "14/7/2", "10/3/1", 2, "Mon 14:00", "Mon 15:00");

    // Mardi
    insertReservation(202, "Analyse de Données", "Dupont", "Jean", "E2", "TP", "20/10", "15/5", 2, "Tue 08:00", "Tue 09:00");
    insertReservation(101, "Algorithmique", "Martin", "Sophie", "E2", "CM", "25/15", "20/10", 2, "Tue 09:00", "Tue 10:00");
    insertReservation(302, "Bases de Données", "Lefevre", "Pierre", "E3", "TD", "20/10/5", "15/5/2", 2, "Tue 09:00", "Tue 10:00");
    insertReservation(201, "Réseaux", "Bertolim", "Maria", "E4", "TP", "15/10", "10/5", 2, "Tue 10:00", "Tue 11:00");
    insertReservation(102, "Systèmes d'Exploitation", "Garcia", "Carlos", "E4", "CM", "18/12", "12/8", 2, "Tue 11:00", "Tue 12:00");
    insertReservation(301, "Programmation Orientée Objet", "Moreau", "Isabelle", "E3", "TD", "30/20", "25/15", 2, "Tue 11:00", "Tue 12:00");
    insertReservation(101, "Intelligence Artificielle", "Durand", "Michel", "E4", "CM", "22/11", "18/8", 2, "Tue 13:00", "Tue 14:00");
    insertReservation(202, "Compilation", "Dupont", "Jean", "E4", "TP", "15/10", "10/7", 2, "Tue 14:00", "Tue 15:00");
    insertReservation(302, "Théorie des Langages", "Martin", "Sophie", "E2", "TD", "16/8", "12/4", 2, "Tue 14:00", "Tue 15:00");
    insertReservation(401, "Sécurité Informatique", "Bertolim", "Maria", "E3", "EXAMEN", "14/7/2", "10/3/1", 2, "Tue 15:00", "Tue 16:00");

    // Mercredi
    insertReservation(101, "Analyse de Données", "Dupont", "Jean", "E2", "CM", "20/10", "15/5", 2, "Wed 08:00", "Wed 09:00");
    insertReservation(201, "Algorithmique", "Martin", "Sophie", "E2", "TP", "25/15", "20/10", 2, "Wed 08:00", "Wed 09:00");
    insertReservation(301, "Bases de Données", "Lefevre", "Pierre", "E3", "TD", "20/10/5", "15/5/2", 2, "Wed 09:00", "Wed 10:00");
    insertReservation(102, "Réseaux", "Bertolim", "Maria", "E4", "CM", "15/10", "10/5", 2, "Wed 10:00", "Wed 11:00");
    insertReservation(202, "Systèmes d'Exploitation", "Garcia", "Carlos", "E4", "TP", "18/12", "12/8", 2, "Wed 10:00", "Wed 11:00");
    insertReservation(101, "Programmation Orientée Objet", "Moreau", "Isabelle", "E3", "CM", "30/20", "25/15", 2, "Wed 11:00", "Wed 12:00");
    insertReservation(302, "Intelligence Artificielle", "Durand", "Michel", "E4", "TD", "22/11", "18/8", 2, "Wed 11:00", "Wed 12:00");
    insertReservation(201, "Compilation", "Dupont", "Jean", "E4", "TP", "15/10", "10/7", 2, "Wed 13:00", "Wed 14:00");
    insertReservation(102, "Théorie des Langages", "Martin", "Sophie", "E2", "CM", "16/8", "12/4", 2, "Wed 14:00", "Wed 15:00");
    insertReservation(301, "Sécurité Informatique", "Bertolim", "Maria", "E3", "TD", "14/7/2", "10/3/1", 2, "Wed 14:00", "Wed 15:00");

    // Jeudi
    insertReservation(202, "Analyse de Données", "Dupont", "Jean", "E2", "TP", "20/10", "15/5", 2, "Thu 08:00", "Thu 09:00");
    insertReservation(101, "Algorithmique", "Martin", "Sophie", "E2", "CM", "25/15", "20/10", 2, "Thu 09:00", "Thu 10:00");
    insertReservation(302, "Bases de Données", "Lefevre", "Pierre", "E3", "TD", "20/10/5", "15/5/2", 2, "Thu 09:00", "Thu 10:00");
    insertReservation(201, "Réseaux", "Bertolim", "Maria", "E4", "TP", "15/10", "10/5", 2, "Thu 10:00", "Thu 11:00");
    insertReservation(102, "Systèmes d'Exploitation", "Garcia", "Carlos", "E4", "CM", "18/12", "12/8", 2, "Thu 11:00", "Thu 12:00");
    insertReservation(301, "Programmation Orientée Objet", "Moreau", "Isabelle", "E3", "TD", "30/20", "25/15", 2, "Thu 11:00", "Thu 12:00");
    insertReservation(101, "Intelligence Artificielle", "Durand", "Michel", "E4", "CM", "22/11", "18/8", 2, "Thu 13:00", "Thu 14:00");
    insertReservation(202, "Compilation", "Dupont", "Jean", "E4", "TP", "15/10", "10/7", 2, "Thu 14:00", "Thu 15:00");
    insertReservation(302, "Théorie des Langages", "Martin", "Sophie", "E2", "TD", "16/8", "12/4", 2, "Thu 14:00", "Thu 15:00");
    insertReservation(401, "Sécurité Informatique", "Bertolim", "Maria", "E3", "EXAMEN", "14/7/2", "10/3/1", 2, "Thu 15:00", "Thu 16:00");

    // Vendredi
    insertReservation(101, "Analyse de Données", "Dupont", "Jean", "E2", "CM", "20/10", "15/5", 2, "Fri 08:00", "Fri 09:00");
    insertReservation(201, "Algorithmique", "Martin", "Sophie", "E2", "TP", "25/15", "20/10", 2, "Fri 08:00", "Fri 09:00");
    insertReservation(301, "Bases de Données", "Lefevre", "Pierre", "E3", "TD", "20/10/5", "15/5/2", 2, "Fri 09:00", "Fri 10:00");
    insertReservation(102, "Réseaux", "Bertolim", "Maria", "E4", "CM", "15/10", "10/5", 2, "Fri 10:00", "Fri 11:00");
    insertReservation(202, "Systèmes d'Exploitation", "Garcia", "Carlos", "E4", "TP", "18/12", "12/8", 2, "Fri 10:00", "Fri 11:00");
    insertReservation(101, "Programmation Orientée Objet", "Moreau", "Isabelle", "E3", "CM", "30/20", "25/15", 2, "Fri 11:00", "Fri 12:00");
    insertReservation(302, "Intelligence Artificielle", "Durand", "Michel", "E4", "TD", "22/11", "18/8", 2, "Fri 11:00", "Fri 12:00");
    insertReservation(201, "Compilation", "Dupont", "Jean", "E4", "TP", "15/10", "10/7", 2, "Fri 13:00", "Fri 14:00");
    insertReservation(102, "Théorie des Langages", "Martin", "Sophie", "E2", "CM", "16/8", "12/4", 2, "Fri 14:00", "Fri 15:00");
    insertReservation(301, "Sécurité Informatique", "Bertolim", "Maria", "E3", "TD", "14/7/2", "10/3/1", 2, "Fri 14:00", "Fri 15:00");

    // Semaine 3
    // Lundi
    insertReservation(401, "Analyse de Données", "Dupont", "Jean", "E2", "EXAMEN", "20/10", "15/5", 3, "Mon 08:00", "Mon 09:00");
    insertReservation(402, "Algorithmique", "Martin", "Sophie", "E2", "EXAMEN", "25/15", "20/10", 3, "Mon 09:00", "Mon 10:00");
    insertReservation(401, "Bases de Données", "Lefevre", "Pierre", "E3", "EXAMEN", "20/10/5", "15/5/2", 3, "Mon 10:00", "Mon 11:00");
    insertReservation(402, "Réseaux", "Bertolim", "Maria", "E4", "EXAMEN", "15/10", "10/5", 3, "Mon 11:00", "Mon 12:00");
    insertReservation(401, "Systèmes d'Exploitation", "Garcia", "Carlos", "E4", "EXAMEN", "18/12", "12/8", 3, "Mon 13:00", "Mon 14:00");
    insertReservation(402, "Programmation Orientée Objet", "Moreau", "Isabelle", "E3", "EXAMEN", "30/20", "25/15", 3, "Mon 14:00", "Mon 15:00");

    // Mardi
    insertReservation(401, "Intelligence Artificielle", "Durand", "Michel", "E4", "EXAMEN", "22/11", "18/8", 3, "Tue 08:00", "Tue 09:00");
    insertReservation(402, "Compilation", "Dupont", "Jean", "E4", "EXAMEN", "15/10", "10/7", 3, "Tue 09:00", "Tue 10:00");
    insertReservation(401, "Théorie des Langages", "Martin", "Sophie", "E2", "EXAMEN", "16/8", "12/4", 3, "Tue 10:00", "Tue 11:00");

    // Mercredi
    insertReservation(402, "Sécurité Informatique", "Bertolim", "Maria", "E3", "EXAMEN", "14/7/2", "10/3/1", 3, "Wed 08:00", "Wed 09:00");
}

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    // Global Database Object (Alternatively, you can pass this to functions)
    QSqlDatabase db;

    // Initialize the database
    initDatabase(db);

    //creerReservation();

    QList<int> roomNumbers = readRoomNumbersFromCSV(QString::fromStdString("EXAMEN"));
    for (int roomNumber : roomNumbers) {
        qDebug() << roomNumber;
    }

    salleLibreSemaine(3, roomNumbers);

    db.close();

    popupEdt *popup = new popupEdt();

    popup->show();


/*
    // Input start and finish times
    int targetSemaine = 2;
    QString targetDebut = "Mon 10:15";
    QString targetFin = "Mon 12:00";

    // Check availability for each room
    qDebug() << "Rooms available from" << targetDebut << "to" << targetFin << "in week" << targetSemaine << ":";
    for (int roomNumber : roomNumbers) {
        if (isRoomAvailable(roomNumber, targetSemaine, targetDebut, targetFin)) {
            qDebug() << roomNumber;
        }
    }

    // Fetch and print all reservations
    qDebug() << "All Reservations:";
    QList<QVariantMap> allReservations = getAllReservations();
    for (const auto& reservation : allReservations) {
        afficherQMap(reservation);
    }

    // Fetch and print reservations for room 103
    qDebug() << "\nReservations for Room 103:";
    QList<QVariantMap> roomReservations = getReservationsByRoom("103");
    for (const auto& reservation : roomReservations) {
        afficherQMap(reservation);
    }

    // Fetch and print reservations for teacher "Bertolim"
    qDebug() << "\nReservations for Teacher Bertolim:";
    QList<QVariantMap> teacherReservations = getReservationsByTeacher("Bertolim");
    for (const auto& reservation : teacherReservations) {
        afficherQMap(reservation);
    }
*/
    return a.exec();
}

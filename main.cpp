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
    insertReservation(101, "Mathématiques", "Dupont", "Jean", "E1", "CM", "20/0/0", "18/0/0", 1, "Mon 08:00", "Mon 09:30");
    insertReservation(201, "Physique", "Bertolim", "Maria", "E2", "TP", "0/20/0", "0/17/0", 1, "Mon 08:00", "Mon 10:00");
    insertReservation(301, "Informatique", "Martin", "Sophie", "E3", "TD", "0/0/20", "0/0/18", 1, "Mon 09:00", "Mon 10:30");
    insertReservation(102, "Anglais", "Lefevre", "Pierre", "E4", "CM", "15/0/0", "13/0/0", 1, "Mon 10:00", "Mon 11:30");
    insertReservation(202, "Economie", "Garcia", "Carlos", "E5", "TP", "0/15/0", "0/13/0", 1, "Mon 10:30", "Mon 12:00");
    insertReservation(103, "Mathématiques", "Durand", "Michel", "E2", "CM", "20/0/0", "18/0/0", 1, "Mon 13:00", "Mon 14:30");
    insertReservation(302, "Informatique", "Moreau", "Isabelle", "E1", "TD", "0/0/20", "0/0/17", 1, "Mon 14:00", "Mon 15:30");
    insertReservation(203, "Physique", "Dupont", "Jean", "E3", "TP", "0/20/0", "0/17/0", 1, "Mon 15:00", "Mon 17:00");

    // Mardi
    insertReservation(101, "Informatique", "Martin", "Sophie", "E1", "CM", "25/0/0", "23/0/0", 1, "Tue 08:30", "Tue 10:00");
    insertReservation(301, "Anglais", "Lefevre", "Pierre", "E2", "TD", "0/0/15", "0/0/13", 1, "Tue 09:00", "Tue 10:30");
    insertReservation(201, "Economie", "Garcia", "Carlos", "E3", "TP", "0/15/0", "0/11/0", 1, "Tue 10:00", "Tue 12:00");
    insertReservation(102, "Mathématiques", "Durand", "Michel", "E4", "CM", "20/0/0", "16/0/0", 1, "Tue 13:30", "Tue 15:00");
    insertReservation(302, "Physique", "Bertolim", "Maria", "E5", "TD", "0/0/20", "0/0/16", 1, "Tue 14:00", "Tue 15:30");
    insertReservation(202, "Informatique", "Moreau", "Isabelle", "E1", "TP", "0/25/0", "0/23/0", 1, "Tue 15:30", "Tue 17:30");

    // Mercredi
    insertReservation(103, "Anglais", "Lefevre", "Pierre", "E3", "CM", "15/0/0", "11/0/0", 1, "Wed 08:00", "Wed 09:30");
    insertReservation(203, "Economie", "Garcia", "Carlos", "E4", "TP", "0/15/0", "0/11/0", 1, "Wed 09:00", "Wed 11:00");
    insertReservation(303, "Mathématiques", "Dupont", "Jean", "E5", "TD", "0/0/20", "0/0/16", 1, "Wed 10:00", "Wed 11:30");
    insertReservation(101, "Physique", "Bertolim", "Maria", "E1", "CM", "20/0/0", "16/0/0", 1, "Wed 13:00", "Wed 14:30");
    insertReservation(201, "Informatique", "Martin", "Sophie", "E2", "TP", "0/25/0", "0/21/0", 1, "Wed 14:00", "Wed 16:00");
    insertReservation(301, "Anglais", "Moreau", "Isabelle", "E3", "TD", "0/0/15", "0/0/11", 1, "Wed 15:00", "Wed 16:30");

    // Jeudi
    insertReservation(102, "Economie", "Garcia", "Carlos", "E1", "CM", "10/0/0", "8/0/0", 1, "Thu 08:30", "Thu 10:00");
    insertReservation(202, "Mathématiques", "Durand", "Michel", "E2", "TP", "0/20/0", "0/16/0", 1, "Thu 09:00", "Thu 11:00");
    insertReservation(302, "Physique", "Bertolim", "Maria", "E3", "TD", "0/0/20", "0/0/16", 1, "Thu 10:30", "Thu 12:00");
    insertReservation(103, "Informatique", "Martin", "Sophie", "E4", "CM", "25/0/0", "21/0/0", 1, "Thu 13:30", "Thu 15:00");
    insertReservation(203, "Anglais", "Lefevre", "Pierre", "E5", "TP", "0/15/0", "0/11/0", 1, "Thu 14:00", "Thu 16:00");
    insertReservation(303, "Economie", "Garcia", "Carlos", "E1", "TD", "0/0/10", "0/0/8", 1, "Thu 15:30", "Thu 17:00");

    // Vendredi
    insertReservation(101, "Physique", "Dupont", "Jean", "E2", "CM", "20/0/0", "16/0/0", 1, "Fri 08:00", "Fri 09:30");
    insertReservation(201, "Informatique", "Moreau", "Isabelle", "E3", "TP", "0/25/0", "0/21/0", 1, "Fri 08:30", "Fri 10:30");
    insertReservation(301, "Mathématiques", "Durand", "Michel", "E4", "TD", "0/0/20", "0/0/16", 1, "Fri 09:00", "Fri 10:30");
    insertReservation(102, "Anglais", "Lefevre", "Pierre", "E5", "CM", "15/0/0", "11/0/0", 1, "Fri 10:00", "Fri 11:30");
    insertReservation(202, "Economie", "Bertolim", "Maria", "E1", "TP", "0/10/0", "0/8/0", 1, "Fri 11:00", "Fri 13:00");
    insertReservation(103, "Informatique", "Martin", "Sophie", "E2", "CM", "25/0/0", "21/0/0", 1, "Fri 13:30", "Fri 15:00");
    insertReservation(302, "Physique", "Dupont", "Jean", "E3", "TD", "0/0/20", "0/0/16", 1, "Fri 14:00", "Fri 15:30");
    insertReservation(203, "Mathématiques", "Moreau", "Isabelle", "E4", "TP", "0/20/0", "0/16/0", 1, "Fri 15:00", "Fri 17:00");

    // Semaine 2
    // Lundi
    insertReservation(101, "Mathématiques", "Dupont", "Jean", "E1", "CM", "20/0/0", "16/0/0", 2, "Mon 08:00", "Mon 09:30");
    insertReservation(201, "Physique", "Bertolim", "Maria", "E2", "TP", "0/20/0", "0/15/0", 2, "Mon 08:00", "Mon 10:00");
    insertReservation(301, "Informatique", "Martin", "Sophie", "E3", "TD", "0/0/25", "0/0/20", 2, "Mon 09:00", "Mon 10:30");
    insertReservation(102, "Anglais", "Lefevre", "Pierre", "E4", "CM", "15/0/0", "10/0/0", 2, "Mon 10:00", "Mon 11:30");
    insertReservation(202, "Economie", "Garcia", "Carlos", "E5", "TP", "0/15/0", "0/10/0", 2, "Mon 10:30", "Mon 12:00");
    insertReservation(103, "Mathématiques", "Durand", "Michel", "E2", "CM", "20/0/0", "14/0/0", 2, "Mon 13:00", "Mon 14:30");
    insertReservation(302, "Informatique", "Moreau", "Isabelle", "E1", "TD", "0/0/25", "0/0/19", 2, "Mon 14:00", "Mon 15:30");
    insertReservation(203, "Physique", "Dupont", "Jean", "E3", "TP", "0/20/0", "0/13/0", 2, "Mon 15:00", "Mon 17:00");

    // Mardi
    insertReservation(101, "Informatique", "Martin", "Sophie", "E1", "CM", "25/0/0", "20/0/0", 2, "Tue 08:30", "Tue 10:00");
    insertReservation(301, "Anglais", "Lefevre", "Pierre", "E2", "TD", "0/0/15", "0/0/10", 2, "Tue 09:00", "Tue 10:30");
    insertReservation(201, "Economie", "Garcia", "Carlos", "E3", "TP", "0/15/0", "0/8/0", 2, "Tue 10:00", "Tue 12:00");
    insertReservation(102, "Mathématiques", "Durand", "Michel", "E4", "CM", "20/0/0", "12/0/0", 2, "Tue 13:30", "Tue 15:00");
    insertReservation(302, "Physique", "Bertolim", "Maria", "E5", "TD", "0/0/20", "0/0/13", 2, "Tue 14:00", "Tue 15:30");
    insertReservation(202, "Informatique", "Moreau", "Isabelle", "E1", "TP", "0/25/0", "0/20/0", 2, "Tue 15:30", "Tue 17:30");

    // Mercredi
    insertReservation(103, "Anglais", "Lefevre", "Pierre", "E3", "CM", "15/0/0", "8/0/0", 2, "Wed 08:00", "Wed 09:30");
    insertReservation(203, "Economie", "Garcia", "Carlos", "E4", "TP", "0/15/0", "0/6/0", 2, "Wed 09:00", "Wed 11:00");
    insertReservation(303, "Mathématiques", "Dupont", "Jean", "E5", "TD", "0/0/20", "0/0/12", 2, "Wed 10:00", "Wed 11:30");
    insertReservation(101, "Physique", "Bertolim", "Maria", "E1", "CM", "20/0/0", "14/0/0", 2, "Wed 13:00", "Wed 14:30");
    insertReservation(201, "Informatique", "Martin", "Sophie", "E2", "TP", "0/25/0", "0/18/0", 2, "Wed 14:00", "Wed 16:00");
    insertReservation(301, "Anglais", "Moreau", "Isabelle", "E3", "TD", "0/0/15", "0/0/8", 2, "Wed 15:00", "Wed 16:30");

    // Jeudi
    insertReservation(102, "Economie", "Garcia", "Carlos", "E1", "CM", "10/0/0", "6/0/0", 2, "Thu 08:30", "Thu 10:00");
    insertReservation(202, "Mathématiques", "Durand", "Michel", "E2", "TP", "0/20/0", "0/14/0", 2, "Thu 09:00", "Thu 11:00");
    insertReservation(302, "Physique", "Bertolim", "Maria", "E3", "TD", "0/0/20", "0/0/11", 2, "Thu 10:30", "Thu 12:00");
    insertReservation(103, "Informatique", "Martin", "Sophie", "E4", "CM", "25/0/0", "18/0/0", 2, "Thu 13:30", "Thu 15:00");
    insertReservation(203, "Anglais", "Lefevre", "Pierre", "E5", "TP", "0/15/0", "0/6/0", 2, "Thu 14:00", "Thu 16:00");
    insertReservation(303, "Economie", "Garcia", "Carlos", "E1", "TD", "0/0/10", "0/0/6", 2, "Thu 15:30", "Thu 17:00");

    // Vendredi
    insertReservation(101, "Physique", "Dupont", "Jean", "E2", "CM", "20/0/0", "12/0/0", 2, "Fri 08:00", "Fri 09:30");
    insertReservation(201, "Informatique", "Moreau", "Isabelle", "E3", "TP", "0/25/0", "0/16/0", 2, "Fri 08:30", "Fri 10:30");
    insertReservation(301, "Mathématiques", "Durand", "Michel", "E4", "TD", "0/0/20", "0/0/10", 2, "Fri 09:00", "Fri 10:30");
    insertReservation(102, "Anglais", "Lefevre", "Pierre", "E5", "CM", "15/0/0", "6/0/0", 2, "Fri 10:00", "Fri 11:30");
    insertReservation(202, "Economie", "Bertolim", "Maria", "E1", "TP", "0/10/0", "0/6/0", 2, "Fri 11:00", "Fri 13:00");
    insertReservation(103, "Informatique", "Martin", "Sophie", "E2", "CM", "25/0/0", "16/0/0", 2, "Fri 13:30", "Fri 15:00");
    insertReservation(302, "Physique", "Dupont", "Jean", "E3", "TD", "0/0/20", "0/0/8", 2, "Fri 14:00", "Fri 15:30");
    insertReservation(203, "Mathématiques", "Moreau", "Isabelle", "E4", "TP", "0/20/0", "0/12/0", 2, "Fri 15:00", "Fri 17:00");

    // Semaine 3
    // Lundi
    insertReservation(401, "Mathématiques", "Dupont", "Jean", "E1", "EXAMEN", "20/0/2", "0/0/2", 3, "Mon 08:00", "Mon 10:00");
    insertReservation(402, "Physique", "Bertolim", "Maria", "E2", "EXAMEN", "20/5/2", "0/0/2", 3, "Mon 08:00", "Mon 10:00");
    insertReservation(401, "Informatique", "Martin", "Sophie", "E3", "EXAMEN", "25/0/2", "0/0/2", 3, "Mon 10:00", "Mon 12:00");
    insertReservation(402, "Anglais", "Lefevre", "Pierre", "E4", "EXAMEN", "15/0/2", "0/0/2", 3, "Mon 10:00", "Mon 12:00");
    insertReservation(401, "Economie", "Garcia", "Carlos", "E5", "EXAMEN", "10/15/2", "0/0/2", 3, "Mon 13:00", "Mon 15:00");

    // Mardi
    insertReservation(402, "Mathématiques", "Durand", "Michel", "E4", "EXAMEN", "20/0/2", "0/0/2", 3, "Tue 13:30", "Tue 15:30");
    insertReservation(401, "Physique", "Bertolim", "Maria", "E5", "EXAMEN", "20/5/2", "0/0/2", 3, "Tue 15:30", "Tue 17:30");

    // Mercredi
    insertReservation(401, "Anglais", "Lefevre", "Pierre", "E3", "EXAMEN", "15/0/2", "0/0/2", 3, "Wed 10:00", "Wed 12:00");

    // Jeudi
    insertReservation(402, "Informatique", "Martin", "Sophie", "E4", "EXAMEN", "25/0/2", "0/0/2", 3, "Thu 13:30", "Thu 15:30");

    // Vendredi
    insertReservation(401, "Physique", "Dupont", "Jean", "E2", "EXAMEN", "20/0/2", "0/0/2", 3, "Fri 08:00", "Fri 10:00");
    insertReservation(402, "Informatique", "Moreau", "Isabelle", "E3", "EXAMEN", "25/0/2", "0/0/2", 3, "Fri 10:00", "Fri 12:00");
}

int main(int argc, char *argv[]) {
    EcueControleur ecue;

    std::string nomECUE = "Blabla";
    std::string nomEnseignant = "Trenchant";
    std::string prenomEnseignant = "Vincent";
    int numeroSalle = 101;
    cours typeSalle = CM;
    std::string groupeEtudiant = "E4";

    std::vector<cours> types = {CM, TD, TP_INFO};
    std::vector<int> heures = {10, 20, 15};
    ecue.creerECUE(nomECUE, nomEnseignant, prenomEnseignant, numeroSalle, types, heures, groupeEtudiant);

    int heuresCM = ecue.getNombreHeure(typeSalle);
    std::cout << "Nombre d'heures pour CM : " << heuresCM << std::endl;

    int heuresTP = ecue.getNombreHeure(TP_ELEC);
    std::cout << "Nombre d'heures pour TP_ELEC : " << heuresTP << std::endl;

    QCoreApplication a(argc, argv);

    // Global Database Object (Alternatively, you can pass this to functions)
    QSqlDatabase db;

    // Initialize the database
    initDatabase(db);

    creerReservation();

    QList<int> roomNumbers = readRoomNumbersFromCSV(QString::fromStdString("EXAMEN"));
    for (int roomNumber : roomNumbers) {
        qDebug() << roomNumber;
    }

    salleLibreSemaine(3, roomNumbers);
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
    return 0;
}

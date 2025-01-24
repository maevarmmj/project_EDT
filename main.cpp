#include "main.h"
#include <iostream>


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
    
    ajouterSalleCSV(213, CM);
    ajouterSalleCSV(200, TP_INFO);
    ajouterSalleCSV(213, EXAMEN);
    ajouterSalleCSV(103, CM);
    retirerSalleCSV(213);
    ajouterSalleCSV(213, EXAMEN);
    retirerSalleCSV(551);
    retirerSalleCSV(103);

    QCoreApplication a(argc, argv);

    // Global Database Object (Alternatively, you can pass this to functions)
    QSqlDatabase db;

    // Initialize the database
    initDatabase(db);

    // Insert some reservations
    insertReservation(605, "Physique", "Held", 2, "Tue 15:00", "Tue 16:30");
    insertReservation(605, "Maths", "Trenchant", 2, "Tue 15:00", "Tue 16:30");

    insertReservation(103, "TNS", "Trenchant", 1, "Mon 08:45", "Mon 10:00"); // Successful
    insertReservation(103, "TNS", "Trenchant", 1, "Mon 08:45", "Mon 10:00"); // Fails (duplicate)
    insertReservation(103, "Analyse", "toto", 1, "Mon 09:00", "Mon 10:30");    // Fails (time overlap)
    insertReservation(103, "Analyse", "toto", 1, "Mon 08:00", "Mon 08:50");  //fail
    insertReservation(103, "Analyse", "toto", 1, "Mon 10:00", "Mon 10:30");  //successful
    insertReservation(111, "Analyse", "toto", 2, "Mon 10:00", "Mon 10:30");  //successful
    insertReservation(111, "Analyse", "toto", 2, "Tue 10:00", "Tue 10:30");  //successful
    insertReservation(111, "Analyse", "toto", 2, "Wed 10:00", "Wed 10:30");  //successful
    insertReservation(111, "Analyse", "toto", 2, "Thi 10:00", "Thi 10:30");  //successful
    insertReservation(111, "Analyse", "toto", 2, "Fri 10:00", "Fri 10:30");  //successful
    insertReservation(200, "Analyse", "toto", 3, "Fri 10:00", "Fri 10:30");  //successful

    QList<int> roomNumbers = readRoomNumbersFromCSV(QString::fromStdString("CM"));
    for (int roomNumber : roomNumbers) {
        qDebug() << roomNumber;
    }

    // Input start and finish times
    int targetSemaine = 2;
    QString targetDebut = "Mon 10:15";
    QString targetFin = "Mon 12:45";

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
        qDebug() << reservation;
    }

    // Fetch and print reservations for room 103
    qDebug() << "\nReservations for Room 103:";
    QList<QVariantMap> roomReservations = getReservationsByRoom("103");
    for (const auto& reservation : roomReservations) {
        qDebug() << reservation;
    }

    // Fetch and print reservations for teacher "Trenchant"
    qDebug() << "\nReservations for Teacher Trenchant:";
    QList<QVariantMap> teacherReservations = getReservationsByTeacher("Trenchant");
    for (const auto& reservation : teacherReservations) {
        qDebug() << reservation;
    }

    // Delete a reservation (optional)
    deleteReservation(2);

    // Close the database connection (optional, but good practice)
    db.close();

    return 0;
    retirerEnseignantCSV("Trenchant", "Vincent");
    retirerEnseignantCSV("Schlinquer", "Thomas");

    ajouterEnseignantCSV("Bertolim", "M-A");
    ajouterEnseignantCSV("Trenchant", "Vincent");



    ajouterGroupeEtudiantCSV("E1");
    ajouterGroupeEtudiantCSV("E2");
    ajouterGroupeEtudiantCSV("E3");
    ajouterGroupeEtudiantCSV("E4");
    ajouterGroupeEtudiantCSV("E5");






}

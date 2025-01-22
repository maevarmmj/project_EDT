#include "CreneauControl.h"

tm setJourHeure(int jourSemaine, int heure){
    tm jourHeure;
    jourHeure.tm_wday = jourSemaine;
    jourHeure.tm_hour = heure;
    return jourHeure;
}

int createDatabase(QSqlDatabase db){

    // 3. Open the Database
    if (!db.open()) {
        qDebug() << "Error: Could not open database.";
        qDebug() << db.lastError().text();
        return 1;
    }

    // 4. Create the Reservations Table (if it doesn't exist)
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS Reservations ("
                    "ReservationID INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "NumeroSalle INTEGER NOT NULL,"
                    "ECUE TEXT NOT NULL,"
                    "Enseignant TEXT NOT NULL,"
                    "Debut TEXT NOT NULL,"
                    "Fin TEXT NOT NULL)")) {
        qDebug() << "Error creating table:";
        qDebug() << query.lastError().text();
        return 1;
    }
    return 0;
}

int addreservation(){

    // 1. Set up the Database Connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); // Use SQLite driver

    // 2. Specify Database File Path (similar to before)
    QString dbDirectory = QDir::currentPath() + QString::fromStdString("/../../");
    if (!QDir(dbDirectory).exists()) {
        QDir().mkdir(dbDirectory);
        qDebug() << "Created directory: " << dbDirectory;
    }
    QString dbFilePath = dbDirectory + "/reservations.db";
    db.setDatabaseName(dbFilePath);

    // 3. Open the Database
    if (!db.open()) {
        qDebug() << "Error: Could not open database.";
        qDebug() << db.lastError().text();
        return 1;
    }

    // 4. Create the Reservations Table (if it doesn't exist)
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS Reservations ("
                    "ReservationID INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "NumeroSalle INTEGER NOT NULL,"
                    "ECUE TEXT NOT NULL,"
                    "Enseignant TEXT NOT NULL,"
                    "Debut TEXT NOT NULL,"
                    "Fin TEXT NOT NULL)")) {
        qDebug() << "Error creating table:";
        qDebug() << query.lastError().text();
        return 1;
    }


    // 5. Insert Reservations
    // Function to insert a reservation
    auto insertReservation = [&](const int& NumeroSalle, const QString& ECUE, const QString& Enseignant, const QString& Debut, const QString& Fin) {
        QSqlQuery insertQuery;
        insertQuery.prepare("INSERT INTO Reservations (NumeroSalle, ECUE, Enseignant, Debut, Fin) "
                            "VALUES (:NumeroSalle, :ECUE, :Enseignant, :Debut, :Fin)");
        insertQuery.bindValue(":NumeroSalle", NumeroSalle);
        insertQuery.bindValue(":ECUE", ECUE);
        insertQuery.bindValue(":Enseignant", Enseignant);
        insertQuery.bindValue(":Debut", Debut);
        insertQuery.bindValue(":Fin", Fin);

        if (!insertQuery.exec()) {
            qDebug() << "Error inserting reservation:";
            qDebug() << insertQuery.lastError().text();
        }
    };

    // Example usage
    insertReservation(1, "John Doe", "2024-03-15 10:00", "2024-03-15 12:30", "Requires projector");
    insertReservation(6, "Jane Smith", "2024-03-15 14:00", "2024-03-15 16:00", "");


    // 6. Query Reservations (for a specific room)
    QString targetRoom = "1";
    if (!query.exec("SELECT * FROM Reservations WHERE NumeroSalle = '" + targetRoom + "'")) {
        qDebug() << "Error executing query:";
        qDebug() << query.lastError().text();
        return 1;
    }

    // 7. Process Query Results
    while (query.next()) {
        int reservationID = query.value(0).toInt(); // Assuming ReservationID is the first column
        int NumeroSalle = query.value(1).toInt();
        QString ECUE = query.value(2).toString();
        QString Enseignant = query.value(3).toString();
        QString Debut = query.value(4).toString();
        QString Fin = query.value(5).toString();

        qDebug() << "Reservation ID:" << reservationID;
        qDebug() << "Room ID:" << NumeroSalle;
        qDebug() << "Customer Name:" << ECUE;
        qDebug() << "Start Time:" << Enseignant;
        qDebug() << "End Time:" << Debut;
        qDebug() << "Notes:" << Fin;
        qDebug() << "---";
    }


    // 8. Close the database (optional, RAII in QSqlDatabase will handle it)
    db.close();

    return 0;
}

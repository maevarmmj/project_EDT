#include "CreneauControl.h"

tm setJourHeure(int jourSemaine, int heure){
    tm jourHeure;
    jourHeure.tm_wday = jourSemaine;
    jourHeure.tm_hour = heure;
    return jourHeure;
}

// Function to initialize the database connection
bool initDatabase(QSqlDatabase db) {
    db = QSqlDatabase::addDatabase("QSQLITE");

    // 2. Specify Database File Path
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
        return false;
    }

    // 4. Create the Reservations Table (if it doesn't exist)
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS Reservations ("
                    "ReservationID INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "NumeroSalle INTEGER NOT NULL,"
                    "ECUE TEXT NOT NULL,"
                    "Enseignant TEXT NOT NULL,"
                    "Semaine INTEGER NOT NULL,"
                    "Debut TEXT NOT NULL,"
                    "Fin TEXT NOT NULL)")) {
        qDebug() << "Error creating table";
        qDebug() << query.lastError().text();
        return false;
    }

    return true;
}

bool isRoomAvailable(int NumeroSalle, int Semaine, const QString& Debut, const QString& Fin) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Reservations WHERE NumeroSalle = :NumeroSalle AND Semaine = :Semaine "
                  "AND ((Debut <= :Debut AND Fin > :Debut) OR (Debut < :Fin AND Fin >= :Fin) OR (Debut >= :Debut AND Fin <= :Fin))");
    query.bindValue(":NumeroSalle", NumeroSalle);
    query.bindValue(":Semaine", Semaine);
    query.bindValue(":Debut", Debut);
    query.bindValue(":Fin", Fin);

    if (!query.exec()) {
        qDebug() << "Error checking room availability:" << query.lastError().text();
        return false; // Assume not available on error
    }

    return !query.next(); // Room is available if no matching reservation is found
}



// Function to insert a new reservation
bool insertReservation(int NumeroSalle, const QString& ECUE, const QString& Enseignant, int Semaine, const QString& Debut, const QString& Fin) {

    if (!isRoomAvailable(NumeroSalle, Semaine, Debut, Fin)) {
        qDebug() << "Error: Room" << NumeroSalle << "is not available at the specified time.";
        return false;
    }

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO Reservations (NumeroSalle, ECUE, Enseignant, Semaine, Debut, Fin) "
                        "VALUES (:NumeroSalle, :ECUE, :Enseignant, :Semaine, :Debut, :Fin)");
    insertQuery.bindValue(":NumeroSalle", NumeroSalle);
    insertQuery.bindValue(":ECUE", ECUE);
    insertQuery.bindValue(":Enseignant", Enseignant);
    insertQuery.bindValue(":Semaine", Semaine);
    insertQuery.bindValue(":Debut", Debut);
    insertQuery.bindValue(":Fin", Fin);

    if (!insertQuery.exec()) {
        qDebug() << "Error inserting reservation:";
        qDebug() << insertQuery.lastError().text();
        return false;
    }

    return true;
}

// Function to fetch all reservations
QList<QVariantMap> getAllReservations() {
    QList<QVariantMap> reservations;
    QSqlQuery query("SELECT * FROM Reservations");

    while (query.next()) {
        QVariantMap reservation;
        reservation["ReservationID"] = query.value("ReservationID");
        reservation["NumeroSalle"] = query.value("NumeroSalle");
        reservation["ECUE"] = query.value("ECUE");
        reservation["Enseignant"] = query.value("Enseignant");
        reservation["Semaine"] = query.value("Semaine");
        reservation["Debut"] = query.value("Debut");
        reservation["Fin"] = query.value("Fin");
        reservations.append(reservation);
    }

    if (query.lastError().isValid()) {
        qDebug() << "Error fetching all reservations:" << query.lastError().text();
    }

    return reservations;
}

// Function to fetch reservations for a specific room
QList<QVariantMap> getReservationsByRoom(const QString& NumeroSalle) {
    QList<QVariantMap> reservations;
    QSqlQuery query;
    query.prepare("SELECT * FROM Reservations WHERE NumeroSalle = :NumeroSalle");
    query.bindValue(":NumeroSalle", NumeroSalle);

    if (!query.exec()) {
        qDebug() << "Error fetching reservations by room:" << query.lastError().text();
        return reservations;
    }

    while (query.next()) {
        QVariantMap reservation;
        reservation["ReservationID"] = query.value("ReservationID");
        reservation["NumeroSalle"] = query.value("NumeroSalle");
        reservation["ECUE"] = query.value("ECUE");
        reservation["Enseignant"] = query.value("Enseignant");
        reservation["Semaine"] = query.value("Semaine");
        reservation["Debut"] = query.value("Debut");
        reservation["Fin"] = query.value("Fin");
        reservations.append(reservation);
    }

    return reservations;
}

// Function to fetch reservations for a specific teacher
QList<QVariantMap> getReservationsByTeacher(const QString& Enseignant) {
    QList<QVariantMap> reservations;
    QSqlQuery query;
    query.prepare("SELECT * FROM Reservations WHERE Enseignant = :Enseignant");
    query.bindValue(":Enseignant", Enseignant);

    if (!query.exec()) {
        qDebug() << "Error fetching reservations by teacher:" << query.lastError().text();
        return reservations;
    }

    while (query.next()) {
        QVariantMap reservation;
        reservation["ReservationID"] = query.value("ReservationID");
        reservation["NumeroSalle"] = query.value("NumeroSalle");
        reservation["ECUE"] = query.value("ECUE");
        reservation["Enseignant"] = query.value("Enseignant");
        reservation["Semaine"] = query.value("Semaine");
        reservation["Debut"] = query.value("Debut");
        reservation["Fin"] = query.value("Fin");
        reservations.append(reservation);
    }

    return reservations;
}

// Function to delete a reservation by ID
bool deleteReservation(int reservationID) {
    QSqlQuery query;
    query.prepare("DELETE FROM Reservations WHERE ReservationID = :ReservationID");
    query.bindValue(":ReservationID", reservationID);

    if (!query.exec()) {
        qDebug() << "Error deleting reservation:" << query.lastError().text();
        return false;
    }

    return true;
}

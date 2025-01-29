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
    QString dbDirectory = QDir::currentPath() + QString::fromStdString("/../../CSV/");
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
                    "NomECUE TEXT NOT NULL,"
                    "NomEnseignant TEXT NOT NULL,"
                    "PrenomEnseignant TEXT NOT NULL,"
                    "Groupe TEXT NOT NULL,"
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
bool insertReservation(
    int NumeroSalle, const QString& NomECUE, const QString& NomEnseignant, const QString& PrenomEnseignant,const QString& Groupe,
    int Semaine, const QString& Debut, const QString& Fin) {

    if (!isRoomAvailable(NumeroSalle, Semaine, Debut, Fin)) {
        qDebug() << "Error: Room" << NumeroSalle << "is not available at the specified time.";
        return false;
    }

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO Reservations (NumeroSalle, NomECUE, NomEnseignant, PrenomEnseignant, Groupe, Semaine, Debut, Fin) "
                        "VALUES (:NumeroSalle, :NomECUE, :NomEnseignant, :PrenomEnseignant, :Groupe, :Semaine, :Debut, :Fin)");
    insertQuery.bindValue(":NumeroSalle", NumeroSalle);
    insertQuery.bindValue(":NomECUE", NomECUE);
    insertQuery.bindValue(":NomEnseignant", NomEnseignant);
    insertQuery.bindValue(":PrenomEnseignant", PrenomEnseignant);
    insertQuery.bindValue(":Groupe", Groupe);
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
        reservation["NomECUE"] = query.value("NomECUE");
        reservation["NomEnseignant"] = query.value("NomEnseignant");
        reservation["PrenomEnseignant"] = query.value("PrenomEnseignant");
        reservation["Groupe"] = query.value("Groupe");
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

void salleLibreSemaine(int Semaine, const QList<int>& roomNumbers) {
    // Jours de la semaine
    QStringList days = {"Mon", "Tue", "Wed", "Thu", "Fri"};

    // Heures de début et de fin
    QTime startTime(8, 0);
    QTime endTime(18, 0);

    // Boucle sur les jours de la semaine
    for (const QString& day : days) {
        // Boucle sur les heures
        for (QTime currentTime = startTime; currentTime < endTime; currentTime = currentTime.addSecs(3600)) {
            QTime nextTime = currentTime.addSecs(3600);
            QString timeSlot = QString("%1 %2-%3").arg(day).arg(currentTime.toString("HH:mm")).arg(nextTime.toString("HH:mm"));

            // Liste des salles libres pour ce créneau
            QStringList availableRooms;

            // Boucle sur toutes les salles
            for (int roomNumber : roomNumbers) {
                // Vérifier si la salle est disponible
                if (isRoomAvailable(roomNumber, Semaine, QString("%1 %2").arg(day).arg(currentTime.toString("HH:mm")), QString("%1 %2").arg(day).arg(nextTime.toString("HH:mm")))) {
                    availableRooms.append(QString::number(roomNumber));
                }
            }

            // Afficher les salles libres pour ce créneau
            if (!availableRooms.isEmpty()) {
                qDebug().noquote() << timeSlot << ":" << availableRooms.join(", ");
            } else {
                qDebug().noquote() << timeSlot << ":" << "Aucune salle disponible";
            }
        }
    }
}


// Function to check if a teacher is available at a given time slot
bool isTeacherAvailable(const QString& NomEnseignant, int Semaine, const QString& Debut, const QString& Fin) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Reservations WHERE NomEnseignant = :NomEnseignant AND Semaine = :Semaine "
                  "AND ((Debut <= :Debut AND Fin > :Debut) OR (Debut < :Fin AND Fin >= :Fin) OR (Debut >= :Debut AND Fin <= :Fin))");
    query.bindValue(":NomEnseignant", NomEnseignant);
    query.bindValue(":Semaine", Semaine);
    query.bindValue(":Debut", Debut);
    query.bindValue(":Fin", Fin);

    if (!query.exec()) {
        qDebug() << "Error checking teacher availability:" << query.lastError().text();
        return false;
    }

    return !query.next(); // Teacher is available if no matching reservation is found
}

// Function to check if a group is available at a given time slot
bool isGroupAvailable(const QString& Groupe, int Semaine, const QString& Debut, const QString& Fin) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Reservations WHERE Groupe = :Groupe AND Semaine = :Semaine "
                  "AND ((Debut <= :Debut AND Fin > :Debut) OR (Debut < :Fin AND Fin >= :Fin) OR (Debut >= :Debut AND Fin <= :Fin))");
    query.bindValue(":Groupe", Groupe);
    query.bindValue(":Semaine", Semaine);
    query.bindValue(":Debut", Debut);
    query.bindValue(":Fin", Fin);

    if (!query.exec()) {
        qDebug() << "Error checking group availability:" << query.lastError().text();
        return false;
    }

    return !query.next(); // Group is available if no matching reservation is found
}

void deleteReservationsByTeacher(const QString& NomEnseignant, const QString& PrenomEnseignant) {
    QSqlQuery query;
    query.prepare("DELETE FROM Reservations WHERE NomEnseignant = :NomEnseignant AND PrenomEnseignant = :PrenomEnseignant");
    query.bindValue(":NomEnseignant", NomEnseignant);
    query.bindValue(":PrenomEnseignant", PrenomEnseignant);

    if (!query.exec()) {
        qDebug() << "Error deleting reservations by teacher:" << query.lastError().text();
    }
}

void deleteReservationsByGroup(const QString& groupe) {
    QSqlQuery query;
    query.prepare("DELETE FROM Reservations WHERE Groupe = :Groupe");
    query.bindValue(":Groupe", groupe);

    if (!query.exec()) {
        qDebug() << "Error deleting reservations by group:" << query.lastError().text();
    }
}


void deleteReservationsBySalle(int numeroSalle, cours typeCours){
    QSqlQuery query;
    query.prepare("SELECT * FROM Reservations WHERE NumeroSalle = :NumeroSalle");
    query.bindValue(":NumeroSalle", numeroSalle);

    if (!query.exec()) {
        qDebug() << "Error fetching reservations by room:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        QString nomECUE = query.value("NomECUE").toString();
        QString groupe = query.value("Groupe").toString();

        // Récupérer le nom et le prénom de l'enseignant à partir du CSV
        QString nomEnseignant, prenomEnseignant, typesCours, HeuresCours, HeuresAPlacer;
        QString filePath = QDir::currentPath() + "/../../CSV/" + "Ecue.csv";
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            in.readLine();
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList fields = line.split(",");
                if (fields.size() >= 3 && fields[0] == nomECUE && fields[3] == groupe) {
                    nomEnseignant = fields[1];
                    prenomEnseignant = fields[2];
                    typesCours = fields[4];
                    HeuresCours = fields[5];
                    HeuresAPlacer = fields[6];
                    EcueControleur temps = EcueControleur(nomECUE, nomEnseignant, prenomEnseignant, groupe, typesCours, HeuresCours, HeuresAPlacer);
                    temps.decrementerHeuresCours(typeCours, -1);
                    break;
                }
            }
            file.close();
        }
    }
    query.prepare("DELETE FROM Reservations WHERE NumeroSalle = :NumeroSalle");
    query.bindValue(":NumeroSalle", numeroSalle);

    if (!query.exec()) {
        qDebug() << "Error deleting reservations by room:" << query.lastError().text();
    }
}

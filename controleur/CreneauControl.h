#ifndef CRENEAUCONTROL_H
#define CRENEAUCONTROL_H

#include <QFile>
#include <QTextStream>
#include <QDir>

#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QDebug>
#include <QFileInfo>
#include <QDir>

#include "Model/creneau.h"

tm setJourHeure(int jourSemaine, int heure);
int ajouterreservation();

bool initDatabase(QSqlDatabase db);
bool isRoomAvailable(int NumeroSalle, int Semaine, const QString& Debut, const QString& Fin);
void salleLibreSemaine(int Semaine, const QList<int>& roomNumbers);
bool insertReservation(
    int NumeroSalle, const QString& NomECUE, const QString& NomEnseignant, const QString& PrenomEnseignant,const QString& Groupe,
    const QString& TypeCours, const QString& HeuresCours, const QString& HeuresAPlacer,
    int Semaine, const QString& Debut, const QString& Fin);
QList<QVariantMap> getAllReservations();
bool deleteReservation(int reservationID);
bool isTeacherAvailable(const QString& NomEnseignant, int Semaine, const QString& Debut, const QString& Fin);
bool isGroupAvailable(const QString& Groupe, int Semaine, const QString& Debut, const QString& Fin);

#endif // CRENEAUCONTROL_H

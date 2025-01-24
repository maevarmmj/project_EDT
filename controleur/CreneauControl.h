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
bool insertReservation(int NumeroSalle, const QString& ECUE, const QString& Enseignant, int Semaine, const QString& Debut, const QString& Fin);
QList<QVariantMap> getAllReservations();
QList<QVariantMap> getReservationsByRoom(const QString& NumeroSalle);
QList<QVariantMap> getReservationsByTeacher(const QString& Enseignant);
bool deleteReservation(int reservationID);

#endif // CRENEAUCONTROL_H

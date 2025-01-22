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
int addreservation();

#endif // CRENEAUCONTROL_H

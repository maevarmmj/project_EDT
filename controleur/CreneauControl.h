#ifndef CRENEAUCONTROL_H
#define CRENEAUCONTROL_H


#include "Model/creneau.h"
#include "Controleur/ecuecontroleur.h"
#include "definition.h"

tm setJourHeure(int jourSemaine, int heure);
int ajouterreservation();

bool initDatabase(QSqlDatabase db);
bool isRoomAvailable(int NumeroSalle, int Semaine, const QString& Debut, const QString& Fin);
void salleLibreSemaine(int Semaine, const QList<int>& roomNumbers);
bool insertReservation(
    int NumeroSalle, const QString& NomECUE, const QString& NomEnseignant, const QString& PrenomEnseignant,const QString& Groupe,
    int Semaine, const QString& Debut, const QString& Fin);
QList<QVariantMap> getAllReservations();
bool deleteReservation(int reservationID);
bool isTeacherAvailable(const QString& NomEnseignant, int Semaine, const QString& Debut, const QString& Fin);
bool isGroupAvailable(const QString& Groupe, int Semaine, const QString& Debut, const QString& Fin);
void deleteReservationsByTeacher(const QString& NomEnseignant, const QString& PrenomEnseignant);
void deleteReservationsByGroup(const QString& groupe);
void deleteReservationsByECUE(const QString& groupe,const QString& NomECUE);
void deleteReservationsBySalle(int numeroSalle, cours typeCours);

#endif // CRENEAUCONTROL_H

#ifndef DEFINITION_H
#define DEFINITION_H

#include <string>
#include <QIcon>
#include <QString>
#include <QLabel>

typedef enum cours {CM, TD, TP_INFO, TP_ELEC, EXAMEN} cours;
typedef enum boolean {FALSE, TRUE} boolean;


typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

// QLabel *AJOUT_REUSSI = new QLabel("Ajout réussi !");
// QLabel *SUPPRESSION_REUSSIE = new QLabel("Suppression réussie !");
// QLabel *MANQUE_INFO = new QLabel("Veuillez remplir toutes les informations !");

cours StrToCours(std::string coursStr) ;
std::string  CoursToStr(cours cours) ;


#endif // DEFINITION_H

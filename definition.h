#ifndef DEFINITION_H
#define DEFINITION_H

#include <string>
#include <QIcon>
#include <QString>
#include <QLabel>

typedef enum cours {CM, TD, TP_INFO, TP_ELEC, EXAMEN} cours;
typedef enum boolean {FALSE, TRUE} boolean;

// ---- Pour savoir si la création a été réussie ou non ----
enum class CreationResult {
    Success,
    AlreadyExists,
    Error
};

// ---- Pour savoir si la suppression a été réussie ou non ----

enum class SuppressionResult {
    Success,
    Error
};

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

cours StrToCours(std::string coursStr) ;
std::string  CoursToStr(cours cours) ;


#endif // DEFINITION_H

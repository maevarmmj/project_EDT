#ifndef DEFINITION_H
#define DEFINITION_H

#include <string>

typedef enum cours {CM, TD, TP_INFO, TP_ELEC, EXAMEN} cours;
typedef enum boolean {FALSE, TRUE} boolean;


typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

cours StrToCours(std::string coursStr) ;
std::string  CoursToStr(cours cours) ;

#endif // DEFINITION_H

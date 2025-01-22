#include "main.h"



int main()
{
    ajouterSalleCSV(213, CM);
    ajouterSalleCSV(200, TP_INFO);
    ajouterSalleCSV(213, EXAMEN);
    ajouterSalleCSV(103, CM);
    retirerSalleCSV(213);
    ajouterSalleCSV(213, EXAMEN);
    retirerSalleCSV(551);
    retirerSalleCSV(103);
}

#include "main.h"



int main()
{
    tm jourHeure = setJourHeure(0,8);


    std::cout << jourHeure.tm_hour << std::endl;

    salleLibreHeure(5);

}

#ifndef SALLE_H
#define SALLE_H
#include <iostream>
#include <string>

class Salle
{
private:
    int numero;
    std::string typeSalle;

public:
    Salle();
    Salle(int numero,std::string typeSalle);
    int getNumero();
    std::string getTypeSalle();
    void setTypeSalle();
    void deleteSalle();
    void affiche();
};

#endif // SALLE_H

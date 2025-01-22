#ifndef SALLE_H
#define SALLE_H
#include <iostream>
#include <string>
class Salle
{
private:
    int numero;
    std::string typeSalle;
    bool disponible;

public:
    Salle();
    Salle(int numero,std::string typeSalle);
    int getNumero();
    std::string getTypeSalle();
    void setTypeSalle();
    bool estdisponible();
    void setDisponible();

    void deleteSalle();
    void affiche();
};

#endif // SALLE_H

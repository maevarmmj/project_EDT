#ifndef GROUPEETUDIANT_H
#define GROUPEETUDIANT_H
#include <iostream>

#include <string>

class GroupeEtudiant
{

private:
    std::string nomGroupe;
public:
    GroupeEtudiant();
    GroupeEtudiant(std::string nomGroupe);

    std::string getnomGroupe() const;
    void deleteGroupe();
};

#endif // GROUPEETUDIANT_H

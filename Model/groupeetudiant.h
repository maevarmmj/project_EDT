#ifndef GROUPEETUDIANT_H
#define GROUPEETUDIANT_H

#include "definition.h"

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

bool operator== (GroupeEtudiant &gp1, GroupeEtudiant &gp2);

#endif // GROUPEETUDIANT_H

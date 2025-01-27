#include "main.h"
#include <iostream>

// TEST : EDT WINDOW
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Fenetre principale EDT
    MainWindow *mainWind = new MainWindow();
    mainWind->show();

    // Fenetre Ajout Groupe
    AjouterGroupeWindow w;
    w.show();

    // Fenetre Ajout ECUE
    AjoutEcueWindow E;
    E.show();

    // Fenetre Supprimer Groupe
    SupprimerGroupeWindow s;
    s.show();

    // Fenetre Supprimer Enseignant
    SupprimerEnseignantWindow d;
    d.show();

    // Fenetre Supprimer Salle
    SupprimerSalleWindow p;
    p.show();

    // Fenetre Supprimer ECUE
    // EN COURS

    return a.exec();
}

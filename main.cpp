#include "main.h"
#include <iostream>


int main(int argc, char *argv[]) {
    qputenv("QT_QPA_PLATFORM", "windows:darkmode=0");
    QApplication a(argc, argv);
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

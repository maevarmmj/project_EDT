#include "main.h"
#include <iostream>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Fenetre principale EDT
    MainWindow *mainWind = new MainWindow();
    mainWind->show();

    AjouterGroupeWindow w;
    w.show();
    AjoutEcueWindow E;
    E.show();

    SupprimerGroupeWindow s;
    s.show();
    SupprimerEnseignantWindow d;
    d.show();
    SupprimerSalleWindow p;
    p.show();


    return a.exec();
}

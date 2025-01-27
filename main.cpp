#include "main.h"
#include <iostream>

// TEST : EDT WINDOW
// int main(int argc, char *argv[]) {
//     QApplication a(argc, argv);
//     MainWindow *mainWind = new MainWindow();
//     mainWind->show();
//     return a.exec();
// }

// TEST : FENETRES 1
// int main(int argc, char *argv[]) {
//     QApplication a(argc, argv);
//     AjouterGroupeWindow w;
//     w.show();

//     SupprimerGroupeWindow s;
//     s.show();

//     SupprimerEnseignantWindow d;
//    d.show();
//     return a.exec();
// }

// TEST : FENETRES 2
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    AjoutEcueWindow E;
    SupprimerSalleWindow p;

    p.show();
    E.show();
    return a.exec();
}

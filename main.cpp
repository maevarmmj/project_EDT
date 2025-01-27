#include "main.h"
#include <iostream>


// int main(int argc, char *argv[]) {
//     QApplication a(argc, argv);
//     MainWindow *mainWind = new MainWindow();
//     mainWind->show();
//     return a.exec();
// }

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    AjouterGroupeWindow w;
    w.show();

    SupprimerGroupeWindow s;
    s.show();

    SupprimerEnseignantWindow d;
   d.show();
    return a.exec();
}

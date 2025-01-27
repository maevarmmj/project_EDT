#include "main.h"
#include <iostream>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow *mainWind = new MainWindow();
    mainWind->show();
    return a.exec();
}

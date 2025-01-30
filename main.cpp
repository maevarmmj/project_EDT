#include "main.h"


int main(int argc, char *argv[]) {
    qputenv("QT_QPA_PLATFORM", "windows:darkmode=0");

    QApplication a(argc, argv);
    MainWindow *mainWind = new MainWindow();
    mainWind->show();

    return a.exec();
}

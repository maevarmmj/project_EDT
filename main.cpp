#include "main.h"


int main(int argc, char *argv[]) {
    qputenv("QT_QPA_PLATFORM", "windows:darkmode=0");

    QApplication a(argc, argv);
    QFile File("../../Ressources/stylesheet.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    a.setStyleSheet(StyleSheet);
    MainWindow *mainWind = new MainWindow();
    mainWind->show();

    return a.exec();
}

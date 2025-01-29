#ifndef SUPPRIMERUEWINDOW_H
#define SUPPRIMERUEWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QDir>
#include <QIcon>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>

class SupprimerUEWindow : public QMainWindow {
    Q_OBJECT

public:
    SupprimerUEWindow(QWidget *parent = nullptr);
    void setupUI();

private:
    QVBoxLayout* mainLayout;
    QLabel* ueLabel;
    QComboBox* ueComboBox;
    QPushButton* annulerButton;
    QPushButton* supprimerButton;

    void chargerUEDepuisCSV();
    void supprimerUE();
    void annuler();
};

#endif // SUPPRIMERUEWINDOW_H

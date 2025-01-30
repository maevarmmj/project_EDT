#ifndef AJOUTERUEWINDOW_H
#define AJOUTERUEWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QDir>
#include <QVBoxLayout>
#include <QPushButton>
#include <QIcon>
#include <QFile>
#include <QTextStream>
#include <QScrollArea>
#include <QDebug>
#include <QMessageBox>
#include <QStackedWidget>
#include <QTimer>

#include "definition.h"
#include "qmainwindow.h"

class AjouterUEWindow : public QMainWindow {
    Q_OBJECT

private:
    QVBoxLayout* mainLayout;
    QLabel* ueLabel;
    QLineEdit* ueLineEdit;
    QList<QCheckBox*> ecueCheckBoxes;
    QPushButton* enregistrerButton;
    QGroupBox* ecueGroupBox;
    QPushButton* annulerButton;

    void chargerEcueDepuisCSV();
    void enregistrerUE();
    void annuler();

public:
    AjouterUEWindow(QWidget *parent = nullptr);
    ~AjouterUEWindow();
    void setupUI();


};

#endif // AJOUTERUEWINDOW_H

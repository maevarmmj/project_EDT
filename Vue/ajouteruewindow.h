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

public:
    AjouterUEWindow(QWidget *parent = nullptr);
    void setupUI();
private:
    QVBoxLayout* mainLayout;
    QLabel* ueLabel;
    QLineEdit* ueLineEdit;
    QList<QCheckBox*> ecueCheckBoxes;
    QPushButton* enregistrerButton;
    QGroupBox* ecueGroupBox;
    void chargerEcueDepuisCSV();
    void enregistrerUE();
    QPushButton* annulerButton;
    void annuler();


};

#endif // AJOUTERUEWINDOW_H

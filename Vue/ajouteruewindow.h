#ifndef AJOUTERUEWINDOW_H
#define AJOUTERUEWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QDir>
#include "definition.h"
#include "qmainwindow.h"
#include <QVBoxLayout>
#include <QPushButton>

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

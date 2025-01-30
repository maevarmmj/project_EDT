#ifndef SUPPRIMERSALLEWINDOW_H
#define SUPPRIMERSALLEWINDOW_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QSpinBox>
#include <QFormLayout>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QStackedWidget>

#include "Controleur/SalleControl.h"

class SupprimerSalleWindow : public QWidget
{
    Q_OBJECT

private:
    bool chargerSallesDepuisCSV();
    QComboBox *salleComboBox;
    QSpinBox *salleSpinBox;
    QComboBox *categoryComboBox;
    QLineEdit *nameLineEdit;
    QLineEdit *prenomLineEdit;
    QLineEdit *salleNumberLineEdit;
    QComboBox *typeComboBox;
    QPushButton *saveButton;
    QPushButton *cancelButton;
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QFormLayout *formLayout;
    QComboBox *salleNumberComboBox;

private slots:
    void annuler();
    void supprimer();
    void updateSalleComboBox();


public:
    explicit SupprimerSalleWindow(QWidget *parent = nullptr);
    ~SupprimerSalleWindow();


signals:
    void salleWindowClosed(); // Signal émis à la fenêtre principale
};

#endif // SUPPRIMERSALLEWINDOW_H

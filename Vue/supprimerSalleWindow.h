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

class SupprimerSalleWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SupprimerSalleWindow(QWidget *parent = nullptr);

private slots:
    void annuler();
    void supprimer();

private:
    bool chargerSallesDepuisCSV(); // Charge les numéros de salle depuis un fichier CSV
    QComboBox *salleComboBox;  // Menu déroulant pour sélectionner le numéro de salle
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
};

#endif // SUPPRIMERSALLEWINDOW_H

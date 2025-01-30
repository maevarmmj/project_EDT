#ifndef SUPPRIMERECUEWINDOW_H
#define SUPPRIMERECUEWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QDir>
#include <QLabel>
#include <QStackedWidget>
#include <QTimer>


#include "Controleur/ecuecontroleur.h"

class SupprimerEcueWindow : public QDialog
{
    Q_OBJECT

private:
    QPushButton *deleteButton;
    QPushButton *cancelButton;
    QComboBox *ecueComboBox;
    QComboBox *enseignantNomComboBox;
    QComboBox *enseignantPrenomComboBox;
    QComboBox *groupeComboBox;
    EcueControleur ecue;

    void populateEcueComboBox();
    void updateEnseignantNomComboBox(const QString& ecueName);
    void updateEnseignantPrenomComboBox(const QString& enseignantNom);
    void updateGroupeComboBox(const QString& enseignantPrenom);
    void chargerEcueDepuisCSV();

private slots:
    void onSupprimerClicked();
    void onAnnulerClicked();
    void onEcueSelectionChanged(const QString& ecueName);
    void onEnseignantNomChanged(const QString& enseignantNom);
    void onEnseignantPrenomChanged(const QString& enseignantPrenom);
    void onGroupeChanged(const QString& nomGroupe);
    void updateEcueComboBoxes();


public:
    explicit SupprimerEcueWindow(QWidget *parent = nullptr);
    ~SupprimerEcueWindow();

signals:
    void ecueWindowClosed(); // Signal émis à la fenêtre principale
};

#endif // SUPPRIMERECUEWINDOW_H

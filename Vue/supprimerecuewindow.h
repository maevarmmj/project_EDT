#ifndef SUPPRIMERECUEWINDOW_H
#define SUPPRIMERECUEWINDOW_H

#include "definition.h"
#include "Controleur/ecuecontroleur.h"

class SupprimerEcueWindow : public QMainWindow
{
    Q_OBJECT

private:
    QWidget *centralWidget;
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

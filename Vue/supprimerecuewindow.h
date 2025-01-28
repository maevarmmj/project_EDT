#ifndef SUPPRIMERECUEWINDOW_H
#define SUPPRIMERECUEWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QComboBox>

class SupprimerEcueWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SupprimerEcueWindow(QWidget *parent = nullptr);
    ~SupprimerEcueWindow();

private slots:
    void onSupprimerClicked();    // Slot appelé lorsqu'on clique sur "Supprimer"
    void onAnnulerClicked();      // Slot appelé lorsqu'on clique sur "Annuler"
    void onEcueSelectionChanged(const QString& ecueName);    // Changement de l'ECUE sélectionnée
    void onEnseignantNomChanged(const QString& enseignantNom); // Changement du nom de l'enseignant
    void onEnseignantPrenomChanged(const QString& enseignantPrenom); // Changement du prénom de l'enseignant
    void onGroupeChanged(const QString& nomGroupe);

private:
    QPushButton *deleteButton;
    QPushButton *cancelButton;

    QComboBox *ecueComboBox;           // Menu déroulant pour le nom de l'ECUE
    QComboBox *enseignantNomComboBox;  // Menu déroulant pour le nom de l'enseignant
    QComboBox *enseignantPrenomComboBox; // Menu déroulant pour le prénom de l'enseignant
    QComboBox *groupeComboBox;         // Menu déroulant pour le groupe étudiant


    void populateEcueComboBox();                      // Remplir le menu déroulant des ECUE
    void updateEnseignantNomComboBox(const QString& ecueName);  // Mettre à jour les noms des enseignants
    void updateEnseignantPrenomComboBox(const QString& enseignantNom); // Mettre à jour les prénoms
    void updateGroupeComboBox(const QString& enseignantPrenom);        // Mettre à jour les groupes étudiants
    void chargerEcueDepuisCSV();
};

#endif // SUPPRIMERECUEWINDOW_H

#ifndef SUPPRIMERENSEIGNANTWINDOW_H
#define SUPPRIMERENSEIGNANTWINDOW_H

#include "definition.h"
#include "Controleur/enseignantControl.h"

class SupprimerEnseignantWindow : public QMainWindow {
    Q_OBJECT

private:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QFormLayout *formLayout;
    QComboBox *nameComboBox;
    QComboBox *prenomComboBox;
    QPushButton *deleteButton;
    QPushButton *cancelButton;

    QMap<QString, QStringList> teacherData; // Structure pour stocker les noms et prénoms
    void loadTeachersFromCSV(); // Méthode pour charger les enseignants depuis le fichier CSV

private slots:
    void onDeleteClicked();
    void onCancelClicked();
    void updatePrenomComboBox(const QString &selectedName);
    void updateEnseignantComboBox();


public:
    explicit SupprimerEnseignantWindow(QWidget *parent = nullptr);
    ~SupprimerEnseignantWindow();


signals:
    void windowClosed(); // Signal émis à la fenêtre principale
};


#endif // SUPPRIMERENSEIGNANTWINDOW_H

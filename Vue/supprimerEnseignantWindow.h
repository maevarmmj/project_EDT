#ifndef SUPPRIMERENSEIGNANTWINDOW_H
#define SUPPRIMERENSEIGNANTWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QDir>

class SupprimerEnseignantWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit SupprimerEnseignantWindow(QWidget *parent = nullptr);
    ~SupprimerEnseignantWindow();

private slots:
    void onDeleteClicked();
    void onCancelClicked();
    void updatePrenomComboBox(const QString &selectedName);

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
};


#endif // SUPPRIMERENSEIGNANTWINDOW_H

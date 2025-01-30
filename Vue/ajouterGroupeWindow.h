#ifndef AJOUTERGROUPEWINDOW_H
#define AJOUTERGROUPEWINDOW_H

#include <Controleur/grpeetudiantcontrolleur.h>
#include <controleur/SalleControl.h>
#include <controleur/enseignantControl.h>

#include "definition.h"

class AjouterGroupeWindow : public QMainWindow {
    Q_OBJECT

private:
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

    void createForm();
    void clearForm();

private slots:
    void onCategoryChanged(const QString &category);
    void onSaveClicked();
    void onCancelClicked();

public:
    AjouterGroupeWindow(QWidget *parent = nullptr);
    ~AjouterGroupeWindow();

signals:
    void windowClosed(); // Signal émis à la fenêtre principale

};

#endif // AJOUTERGROUPEWINDOW_H

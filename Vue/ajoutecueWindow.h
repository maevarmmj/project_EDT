#ifndef AJOUT_ECUE_H
#define AJOUT_ECUE_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QDir>

class AjoutEcueWindow : public QWidget {
    Q_OBJECT

public:
    explicit AjoutEcueWindow(QWidget *parent = nullptr);

private slots:
    void toggleCM(int state);
    void toggleTP(int state);
    void toggleTD(int state);
    void toggleExam(int state);
    void enregistrer();
    void annuler();



private:
    QLineEdit *ecueLineEdit;
    QComboBox *groupComboBox;
    QComboBox *teacherComboBox; // Nouveau menu déroulant
    QCheckBox *cmCheckBox;
    QSpinBox *cmSpinBox;
    QCheckBox *tpCheckBox;
    QSpinBox *tpSpinBox;
    QCheckBox *tdCheckBox;
    QSpinBox *tdSpinBox;
    QCheckBox *examCheckBox;
    QSpinBox *examSpinBox;
    QCheckBox *elecCheckBox;
    QCheckBox *infoCheckBox;

    void loadTeachersFromCSV(); // Nouvelle méthode pour charger le fichier CSV

};

#endif // AJOUT_ECUE_H

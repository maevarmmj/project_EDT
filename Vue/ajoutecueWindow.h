#ifndef AJOUT_ECUE_H
#define AJOUT_ECUE_H

#include "definition.h"
#include "Controleur/ecuecontroleur.h"

class AjoutEcueWindow : public QMainWindow {
    Q_OBJECT

private:
    QWidget *centralWidget;
    QLineEdit *ecueLineEdit;
    QComboBox *groupComboBox;
    QComboBox *nomComboBox;
    QComboBox *prenomComboBox;
    QCheckBox *cmCheckBox;
    QSpinBox *cmSpinBox;
    QCheckBox *tpCheckBox;
    QSpinBox *tpSpinBox;
    QCheckBox *tdCheckBox;
    QSpinBox *tdSpinBox;
    QCheckBox *examCheckBox;
    QSpinBox *examSpinBox;
    QCheckBox *elecCheckBox;
    QSpinBox *elecSpinBox;
    QCheckBox *infoCheckBox;
    QSpinBox *infoSpinBox;
    QMap<QString, QStringList> enseignantsData;

    void loadTeachersFromCSV();
    void loadGroupsFromCSV();


private slots:
    void toggleCM(int state);
    void toggleTP(int state);
    void toggleElec(int state);
    void toggleInfo(int state);
    void toggleTD(int state);
    void toggleExam(int state);
    void enregistrer();
    void annuler();
    void updatePrenoms(const QString &nom);

public:
    explicit AjoutEcueWindow(QWidget *parent = nullptr);
    ~AjoutEcueWindow();

signals:
    void windowClosed(); // Signal émis à la fenêtre principale

};

#endif // AJOUT_ECUE_H

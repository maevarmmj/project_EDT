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
    void toggleElec(int state);
    void toggleInfo(int state);
    void toggleTD(int state);
    void toggleExam(int state);
    void enregistrer();
    void annuler();



private:
    QLineEdit *ecueLineEdit;
    QComboBox *groupComboBox;
    QComboBox *teacherComboBox;
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

    void loadTeachersFromCSV();
};

#endif // AJOUT_ECUE_H

#ifndef POPUPEDT_H
#define POPUPEDT_H

#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QComboBox>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>

#include "Controleur/CreneauControl.h"
#include "Controleur/SalleControl.h"

class popupEdt : public QMainWindow
{
    Q_OBJECT
private:
    QSqlDatabase db;
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    // ---------------- Bandeau du Haut --------------------
    QWidget *bandeauWidget;
    QHBoxLayout *bandeauLayout;
    QLabel *semaineLabel;
    QSpinBox *semaineSpinBox;
    QLabel *ecueLabel;
    QComboBox *ecueComboBox;
    QLabel *typeCoursLabel;
    QComboBox *typeCoursComboBox;
    QPushButton *validerButton;
    // ---------------- Bandeau du Bas --------------------
    QWidget *infoWidget;
    QHBoxLayout *infoLayout;
    QLabel *groupeValueLabel;
    QLabel *enseignantValueLabel;
    QLabel *ecueInfoValueLabel;
    QLabel *typeCoursInfoValueLabel;
    // ---------------- Grille de boutons --------------------
    QGridLayout *gridLayout;
    QLabel *dayLabel;
    QLabel *hourLabel;
    QWidget *gridWidget;

    QStringList days;
public:
    popupEdt(QWidget *parent = nullptr);
    ~popupEdt() = default;

private slots :
    void lectureCsvEcue(QComboBox *ecueComboBox, QComboBox *typeCoursComboBox);
    void mettreAJourBandeauBas(QLabel *groupeValueLabel, QLabel *enseignantValueLabel, QLabel *ecueInfoValueLabel, QLabel *typeCoursInfoValueLabel, const QString &ecueLabel, const QString &typeCours);
    void afficherInfosBouton(const QString &ecueLabel, int semaine, int row, int col);
    void validerEtAfficher();
    void bloquerBoutonsIndisponibles(int semaine, const QString& enseignant, const QString& groupe);
};

#endif // POPUPEDT_H

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

class popupEdt : public QMainWindow
{
private:
    void lectureCsvEcue(QComboBox *ecueComboBox, QComboBox *typeCoursComboBox);
    void mettreAJourBandeauBas(QLabel *groupeValueLabel, QLabel *enseignantValueLabel, QLabel *ecueInfoValueLabel, QLabel *typeCoursInfoValueLabel, const QString &ecueLabel, const QString &typeCours);
    void afficherInfosBouton(const QString &ecueLabel, int semaine, int row, int col);
public:
    popupEdt();
    ~popupEdt() = default;
};

#endif // POPUPEDT_H

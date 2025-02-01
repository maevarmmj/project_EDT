#ifndef POPUPEDT_H
#define POPUPEDT_H

#include "Controleur/CreneauControl.h"
#include "Controleur/SalleControl.h"
#include "Controleur/ecuecontroleur.h"
#include "definition.h"

class popupEdt : public QMainWindow
{
    Q_OBJECT

private:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QStackedWidget *messageStack;
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
    // --------------- selection de boutons ------------------
    QList<QPushButton*> selectedButtons;
    QList<QVariantMap> selectedButtonInfos;
    QPushButton *validerButtonGrid;
    QPushButton *annulerButtonGrid;

    QString heuresRestantes;
    int minButtonHeight;
    QStringList days = {"Mon", "Tue", "Wed", "Thu", "Fri"};

private slots :
    void showMessageAndHide (int index);
    void lectureCsvEcue(QComboBox *ecueComboBox, QComboBox *typeCoursComboBox);
    void mettreAJourBandeauBas(QLabel *groupeValueLabel, QLabel *enseignantValueLabel, QLabel *ecueInfoValueLabel, QLabel *typeCoursInfoValueLabel, const QString &ecueLabel, const QString &typeCours);
    void validerEtAfficher();
    void bloquerBoutonsIndisponibles(int semaine, const QString& enseignant, const QString& groupe);
    void validerSelection();
    void annulerSelection();
    void onButtonClicked();
    void resetSelection();
    void onRoomSelected(int roomNumber);
    bool eventFilter(QObject *watched, QEvent *event);
    void replaceComboBox ();

public:
    popupEdt(QWidget *parent = nullptr);
    ~popupEdt();


signals:
    void windowClosed();
};

#endif // POPUPEDT_H

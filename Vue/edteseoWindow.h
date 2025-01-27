#ifndef EDTESEOWINDOW_H
#define EDTESEOWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QComboBox>
#include <QPushButton>
#include <QMenu>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QEnterEvent>

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QDir>

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QComboBox *groupComboBox;
    QTableWidget *table;
    QPushButton *addButton;
    QPushButton *remButton;
    QPushButton *addGroupButton;
    QPushButton *addECUEButton;
    QPushButton *remGroupButton;
    QPushButton *remECUEButton;
    QPushButton *updateButton;

    void setupUI();               // Méthode pour initialiser l'interface
    void setupTable();            // Méthode pour configurer la table
    void setupActions();          // Méthode pour configurer les actions
    void hideButtons();      // Méthode pour cacher les boutons "Groupe" et "ECUE"

private slots:
    void loadGroups();           // Charger les groupes depuis le fichier CSV
    void addGroup();             // Action pour ajouter un groupe
    void addECUE();              // Action pour ajouter une ECUE
    void remGroup();
    void remECUE();
    void toggleButtonsVisibility();
    void toggleRemButtonsVisibility();


    void updateTimetable();      // Action pour mettre à jour l'emploi du temps
    void onComboBoxSelectionChanged(const QString &selectedText);


public:
    explicit MainWindow(QWidget *parent = nullptr);



};


#endif // EDTESEOWINDOW_H

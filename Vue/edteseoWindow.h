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

#include "Vue/popupEdt.h"

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
    QPushButton *remEnseignantButton;
    QPushButton *remSalleButton;
    QPushButton *remECUEButton;
    QPushButton *updateButton;

    void setupUI();               // Méthode pour initialiser l'interface
    void setupTable();            // Méthode pour configurer la table
    void setupActions();          // Méthode pour configurer les actions
    void hideButtons();

private slots:
    void loadGroups();
    void addGroup();
    void addECUE();
    void remGroup();
    void remEnseignant();
    void remSalle();
    void remECUE();
    void toggleButtonsVisibility();
    void toggleRemButtonsVisibility();


    void updateEdt();      // Action pour mettre à jour l'emploi du temps
    void onComboBoxSelectionChanged(const QString &selectedText);


public:
    explicit MainWindow(QWidget *parent = nullptr);



};


#endif // EDTESEOWINDOW_H

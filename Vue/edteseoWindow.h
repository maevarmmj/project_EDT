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

#include "Vue/ajouterGroupeWindow.h"
#include "Vue/ajoutecueWindow.h"
#include "Vue/supprimerGroupeWindow.h"
#include "Vue/supprimerEnseignantWindow.h"
#include "Vue/supprimerSalleWindow.h"
#include "Vue/popupEdt.h"
#include "Vue/supprimerecuewindow.h"

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

    void setupUI();
    void setupTable();
    void setupActions();
    void hideButtons();
    bool checkEnseignantsGroupesFiles();

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
    void refreshMainWindow();
    void updateEdt();
    void onComboBoxSelectionChanged(const QString &selectedText);


public:
    explicit MainWindow(QWidget *parent = nullptr);


};

#endif // EDTESEOWINDOW_H

#ifndef EDTESEOWINDOW_H
#define EDTESEOWINDOW_H

#include "Vue/ajouterGroupeWindow.h"
#include "Vue/ajoutecueWindow.h"
#include "Vue/supprimerGroupeWindow.h"
#include "Vue/supprimerEnseignantWindow.h"
#include "Vue/supprimerSalleWindow.h"
#include "Vue/popupEdt.h"
#include "Vue/supprimerecuewindow.h"
#include "Vue/popupEdt.h"
#include "Vue/AjouterUEWindow.h"
#include "Vue/supprimeruewindow.h"
#include "definition.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QComboBox *groupComboBox;
    QTableWidget *table;
    QPushButton *addButton;
    QPushButton *remButton;
    QListWidget *remOptionsList;
    QListWidget *addOptionsList;
    QTimer *remhideTimer;
    QTimer *addhideTimer;
    QPushButton *updateButton;
    QPushButton *refreshButton;
    QList<QString> rooms;

    void setupUI();
    void setupTable();
    void setupActions();
    void hideButtons();
    bool checkEnseignantsGroupesFiles();
    bool checkECUEFile();

private slots:
    bool eventFilter(QObject *obj, QEvent *event);
    void showOptions(QString remOrAdd);
    void hideOptions(QString remOrAdd);
    void delayedHideOptions(QString remOrAdd);
    void loadGroups(boolean firstTime);
    void addGroup();
    void addECUE();
    void addUE();
    void remGroup();
    void remEnseignant();
    void remSalle();
    void remECUE();
    void remUE();
    void refreshMainWindow();
    void updateEdt();
    void onComboBoxSelectionChanged(const QString &selectedText);


public:
    explicit MainWindow(QWidget *parent = nullptr);

};

#endif // EDTESEOWINDOW_H

#ifndef SUPPRIMERGROUPEWINDOW_H
#define SUPPRIMERGROUPEWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QDir>
#include <QComboBox>
#include <QDir>
#include "Controleur/grpeetudiantcontrolleur.h"

class SupprimerGroupeWindow : public QMainWindow {
    Q_OBJECT

private:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QFormLayout *formLayout;
    QComboBox *groupComboBox;
    QPushButton *deleteButton;
    QPushButton *cancelButton;

    void loadGroupsFromCSV();

private slots:
    void onDeleteClicked();
    void onCancelClicked();
    void updateGroupComboBox();

public:
    explicit SupprimerGroupeWindow(QWidget *parent = nullptr);
    ~SupprimerGroupeWindow();




signals:
    void windowClosed();

};

#endif // SUPPRIMERGROUPEWINDOW_H

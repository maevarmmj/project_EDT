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


class SupprimerGroupeWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit SupprimerGroupeWindow(QWidget *parent = nullptr);
    ~SupprimerGroupeWindow();

private slots:
    void onDeleteClicked();
    void onCancelClicked();

private:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QFormLayout *formLayout;
    QComboBox *groupComboBox;
    QPushButton *deleteButton;
    QPushButton *cancelButton;

    void loadGroupsFromCSV(); // Méthode pour charger les groupes depuis le fichier CSV
};

#endif // SUPPRIMERGROUPEWINDOW_H

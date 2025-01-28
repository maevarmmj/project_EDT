#ifndef AJOUTERGROUPEWINDOW_H
#define AJOUTERGROUPEWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QSpinBox>

class AjouterGroupeWindow : public QMainWindow {
    Q_OBJECT

public:
    AjouterGroupeWindow(QWidget *parent = nullptr);
    ~AjouterGroupeWindow();

private slots:
    void onCategoryChanged(const QString &category);
    void onSaveClicked();
    void onCancelClicked();

private:
    QSpinBox *salleSpinBox;
    QComboBox *categoryComboBox;
    QLineEdit *nameLineEdit;
    QLineEdit *prenomLineEdit;
    QLineEdit *salleNumberLineEdit;
    QComboBox *typeComboBox;
    QPushButton *saveButton;
    QPushButton *cancelButton;
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QFormLayout *formLayout;
    QComboBox *salleNumberComboBox;

    void createForm();
    void clearForm();
};

#endif // AJOUTERGROUPEWINDOW_H

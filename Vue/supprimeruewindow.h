#ifndef SUPPRIMERUEWINDOW_H
#define SUPPRIMERUEWINDOW_H

#include "definition.h"

class SupprimerUEWindow : public QMainWindow {
    Q_OBJECT

public:
    SupprimerUEWindow(QWidget *parent = nullptr);
    ~SupprimerUEWindow();
    void setupUI();

private:
    QVBoxLayout* mainLayout;
    QLabel* ueLabel;
    QComboBox* ueComboBox;
    QPushButton* annulerButton;
    QPushButton* supprimerButton;

    void chargerUEDepuisCSV();
    void supprimerUE();
    void annuler();
};

#endif // SUPPRIMERUEWINDOW_H

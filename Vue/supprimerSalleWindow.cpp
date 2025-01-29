#include "supprimerSalleWindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

SupprimerSalleWindow::SupprimerSalleWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Supprimer un numéro de salle");
    resize(400, 200);
    setWindowModality(Qt::ApplicationModal);
    QString file(QDir::currentPath() + "/../../Ressources/planning.ico");
    QIcon icon(file);
    setWindowIcon(icon);

    QVBoxLayout *mainLayout = new QVBoxLayout();

    QLabel *label = new QLabel("Sélectionnez le numéro de la salle à supprimer :");
    salleComboBox = new QComboBox();

    if (!chargerSallesDepuisCSV()) {
        QMessageBox::warning(this, "Erreur", "Impossible de charger les numéros de salle depuis le fichier Salles.csv.");
    }

    mainLayout->addWidget(label);
    mainLayout->addWidget(salleComboBox);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *annulerButton = new QPushButton("Annuler");
    QPushButton *supprimerButton = new QPushButton("Supprimer");
    annulerButton->setObjectName("cancelButton");
    supprimerButton->setObjectName("deleteButton");
    buttonLayout->addStretch();
    buttonLayout->addWidget(annulerButton);
    buttonLayout->addWidget(supprimerButton);
    buttonLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    connect(annulerButton, &QPushButton::clicked, this, &SupprimerSalleWindow::annuler);
    connect(supprimerButton, &QPushButton::clicked, this, &SupprimerSalleWindow::supprimer);

    connect(this, &SupprimerSalleWindow::salleWindowClosed, this, &SupprimerSalleWindow::updateSalleComboBox);

    setLayout(mainLayout);
}

SupprimerSalleWindow::~SupprimerSalleWindow() {
}

bool SupprimerSalleWindow::chargerSallesDepuisCSV() {
    QFile file(QDir::currentPath() + "/../../CSV/" + "Salles.csv");

    if (!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream in(&file);
    bool firstLine = true;

    while (!in.atEnd()) {
        QString line = in.readLine();

        if (firstLine) {
            firstLine = false;
            continue;
        }

        QStringList values = line.split(",");
        if (!values.isEmpty()) {
            salleComboBox->addItem(values[0].trimmed());
        }
    }

    file.close();
    return true;
}

void SupprimerSalleWindow::updateSalleComboBox() {
    salleComboBox->clear();
    chargerSallesDepuisCSV();
}

void SupprimerSalleWindow::annuler() {
    QMessageBox::information(this,"Annulation", "L'opération est bien annulée");
    emit salleWindowClosed();
    close();
}

void SupprimerSalleWindow::supprimer() {
    QString salleNumber = salleComboBox->currentText();
    if (salleNumber.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le numéro de la salle n'est pas valide.");
        return;
    }
    retirerSalleCSV(salleComboBox->currentText().toInt());
    QMessageBox::information(this, "Succès", QString("La salle numéro %1 a bien été supprimée.").arg(salleNumber));
    emit salleWindowClosed();
}

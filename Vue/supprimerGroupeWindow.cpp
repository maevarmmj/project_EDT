#include "supprimerGroupeWindow.h"
#include <QLabel>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

SupprimerGroupeWindow::SupprimerGroupeWindow(QWidget *parent)
    : QMainWindow(parent) {

    resize(600, 300);
    setWindowTitle("Supprimer un groupe d'étudiants");
    setWindowModality(Qt::ApplicationModal);
    QString file(QDir::currentPath() + "/../../Ressources/planning.ico");
    QIcon icon(file);
    setWindowIcon(icon);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout();
    centralWidget->setLayout(mainLayout);

    QLabel *titleLabel = new QLabel("Supprimer un groupe d'étudiants :", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    formLayout = new QFormLayout();
    groupComboBox = new QComboBox(this);
    formLayout->addRow("Nom du groupe :", groupComboBox);
    mainLayout->addLayout(formLayout);

    loadGroupsFromCSV();

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    deleteButton = new QPushButton("Supprimer", this);
    deleteButton->setObjectName("deleteButton");

    cancelButton = new QPushButton("Annuler", this);
    cancelButton->setObjectName("cancelButton");

    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(deleteButton);
    mainLayout->addLayout(buttonLayout);

    connect(deleteButton, &QPushButton::clicked, this, &SupprimerGroupeWindow::onDeleteClicked);
    connect(cancelButton, &QPushButton::clicked, this, &SupprimerGroupeWindow::onCancelClicked);

        connect(this, &SupprimerGroupeWindow::windowClosed, this, &SupprimerGroupeWindow::updateGroupComboBox);
}

SupprimerGroupeWindow::~SupprimerGroupeWindow() {
    emit windowClosed();
}

void SupprimerGroupeWindow::loadGroupsFromCSV() {
    QFile file(QDir::currentPath() + "/../../CSV/" + "Groupes.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur", "Impossible de lire le fichier Groupes.csv.");
        return;
    }

    QTextStream in(&file);
    bool isFirstLine = true;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }

        if (!line.isEmpty()) {
            QStringList fields = line.split(",");
            if (!fields.isEmpty()) {
                groupComboBox->addItem(fields[0]);
            }
        }
    }
    file.close();
}

void SupprimerGroupeWindow::onDeleteClicked() {
    QString selectedGroup = groupComboBox->currentText();

    if (selectedGroup.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Aucun groupe sélectionné");
        return;
    }
    retirerGroupeEtudiantCSV(selectedGroup.toStdString());
    QMessageBox::information(this, "Succès", QString("Le groupe '%1' a été supprimé").arg(selectedGroup));
    emit windowClosed();
}

void SupprimerGroupeWindow::onCancelClicked() {
    QMessageBox::information(this, "Annulé", "Suppression annulée");
    emit windowClosed();
    close();
}

void SupprimerGroupeWindow::updateGroupComboBox() {
    groupComboBox->clear();
    loadGroupsFromCSV();
}

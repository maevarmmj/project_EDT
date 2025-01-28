#include "supprimerecuewindow.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QDir>
#include <QLabel>

SupprimerEcueWindow::SupprimerEcueWindow(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Supprimer une ECUE");
    resize(400, 300);
    setWindowModality(Qt::ApplicationModal);

    ecueComboBox = new QComboBox();
    enseignantNomComboBox = new QComboBox();
    enseignantPrenomComboBox = new QComboBox();
    groupeComboBox = new QComboBox();

    ecueComboBox->addItem("Sélectionner");

    chargerEcueDepuisCSV();

    QLabel *label = new QLabel("Insérez de l'information de l'ECUE à supprimer");
    label->setAlignment(Qt::AlignHCenter);

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("Nom ECUE :", ecueComboBox);
    formLayout->addRow("Nom Enseignant :", enseignantNomComboBox);
    formLayout->addRow("Prénom Enseignant :", enseignantPrenomComboBox);
    formLayout->addRow("Groupe Étudiant :", groupeComboBox);

    deleteButton = new QPushButton("Supprimer");
    cancelButton = new QPushButton("Annuler");

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(deleteButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(label);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    connect(ecueComboBox, &QComboBox::currentTextChanged, this, &SupprimerEcueWindow::onEcueSelectionChanged);
    connect(enseignantNomComboBox, &QComboBox::currentTextChanged, this, &SupprimerEcueWindow::onEnseignantNomChanged);
    connect(enseignantPrenomComboBox, &QComboBox::currentTextChanged, this, &SupprimerEcueWindow::onEnseignantPrenomChanged);
    connect(groupeComboBox, &QComboBox::currentTextChanged, this, &SupprimerEcueWindow::onGroupeChanged);

    connect(deleteButton, &QPushButton::clicked, this, &SupprimerEcueWindow::onSupprimerClicked);
    connect(cancelButton, &QPushButton::clicked, this, &SupprimerEcueWindow::onAnnulerClicked);

    connect(this, &SupprimerEcueWindow::ecueWindowClosed, this, &SupprimerEcueWindow::updateEcueComboBoxes);
}

SupprimerEcueWindow::~SupprimerEcueWindow() {
}

void SupprimerEcueWindow::chargerEcueDepuisCSV() {
    QString csvPath = QDir::currentPath() + "/../../CSV/Ecue.csv";
    QFile file(csvPath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier Ecue.csv:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    QString line = in.readLine();

    while (!in.atEnd()) {
        line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() > 0) {
            ecueComboBox->addItem(fields[0].trimmed());
        }
    }

    file.close();
}

void SupprimerEcueWindow::onEcueSelectionChanged(const QString &ecue) {
    enseignantNomComboBox->clear();
    enseignantNomComboBox->addItem("Sélectionner");

    if (ecue == "Sélectionner") return;

    QString csvPath = QDir::currentPath() + "/../../CSV/Ecue.csv";
    QFile file(csvPath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier Ecue.csv:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    QString line = in.readLine();

    while (!in.atEnd()) {
        line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() > 1 && fields[0].trimmed() == ecue) {
            enseignantNomComboBox->addItem(fields[1].trimmed());
        }
    }

    file.close();
}

void SupprimerEcueWindow::onEnseignantNomChanged(const QString &nom) {
    enseignantPrenomComboBox->clear();

    QString ecue = ecueComboBox->currentText();
    QString csvPath = QDir::currentPath() + "/../../CSV/Ecue.csv";
    QFile file(csvPath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier Ecue.csv:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    QString line = in.readLine();

    while (!in.atEnd()) {
        line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() > 2 && fields[0].trimmed() == ecue && fields[1].trimmed() == nom) {
            enseignantPrenomComboBox->addItem(fields[2].trimmed());
        }
    }

    file.close();
}

void SupprimerEcueWindow::onEnseignantPrenomChanged(const QString &prenom) {
    groupeComboBox->clear();


    QString ecue = ecueComboBox->currentText();
    QString nom = enseignantNomComboBox->currentText();
    QString csvPath = QDir::currentPath() + "/../../CSV/Ecue.csv";
    QFile file(csvPath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier Ecue.csv:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    QString line = in.readLine();

    while (!in.atEnd()) {
        line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() > 3 && fields[0].trimmed() == ecue && fields[1].trimmed() == nom && fields[2].trimmed() == prenom) {
            groupeComboBox->addItem(fields[3].trimmed());
        }
    }

    file.close();
}

void SupprimerEcueWindow::onGroupeChanged(const QString &groupe) {
    if (groupe == "Sélectionner") return;

    QString ecue = ecueComboBox->currentText();
    QString nom = enseignantNomComboBox->currentText();
    QString prenom = enseignantPrenomComboBox->currentText();

    qDebug() << "Groupe sélectionné :" << groupe;
    qDebug() << "ECUE :" << ecue << ", Nom :" << nom << ", Prénom :" << prenom;

    QMessageBox::information(this, "Groupe sélectionné",
                             QString("Groupe sélectionné : %1\nECUE : %2\nEnseignant : %3 %4")
                                 .arg(groupe).arg(ecue).arg(nom).arg(prenom));
}



void SupprimerEcueWindow::onSupprimerClicked()
{
    QString ecueName = ecueComboBox->currentText();
    QString enseignantNom = enseignantNomComboBox->currentText();
    QString enseignantPrenom = enseignantPrenomComboBox->currentText();
    QString groupe = groupeComboBox->currentText();

    if (ecueName.isEmpty() || enseignantNom.isEmpty() || enseignantPrenom.isEmpty() || groupe.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Tous les champs doivent être remplis !");
        return;
    }

    ecue.retirerECUECSV(ecueName.toStdString(), enseignantNom.toStdString(), enseignantPrenom.toStdString(), groupe.toStdString());
    QMessageBox::information(this, "Succès", "L'ECUE a été supprimée avec succès !");
    emit ecueWindowClosed();

}



void SupprimerEcueWindow::onAnnulerClicked() {
    QMessageBox::information(this,"Annulation", "L'opération est bien annulée");
    emit ecueWindowClosed();
    close();
}

void SupprimerEcueWindow::updateEcueComboBoxes() {
    ecueComboBox->clear();
    enseignantNomComboBox->clear();
    enseignantPrenomComboBox->clear();
    groupeComboBox->clear();

    ecueComboBox->addItem("Sélectionner");

    chargerEcueDepuisCSV();


}

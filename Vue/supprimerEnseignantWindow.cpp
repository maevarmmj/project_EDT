#include "supprimerEnseignantWindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

SupprimerEnseignantWindow::SupprimerEnseignantWindow(QWidget *parent)
    : QMainWindow(parent) {

    resize(600, 300);
    setWindowTitle("Supprimer un enseignant");
    setWindowModality(Qt::ApplicationModal);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout();
    centralWidget->setLayout(mainLayout);

    QLabel *titleLabel = new QLabel("Supprimer un enseignant :", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    formLayout = new QFormLayout();
    nameComboBox = new QComboBox(this);
    prenomComboBox = new QComboBox(this);

    formLayout->addRow("Nom :", nameComboBox);
    formLayout->addRow("Prénom :", prenomComboBox);
    mainLayout->addLayout(formLayout);

    loadTeachersFromCSV();

    connect(nameComboBox, &QComboBox::currentTextChanged, this, &SupprimerEnseignantWindow::updatePrenomComboBox);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    deleteButton = new QPushButton("Supprimer", this);
    deleteButton->setObjectName("deleteButton");

    cancelButton = new QPushButton("Annuler", this);
    cancelButton->setObjectName("cancelButton");

    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(deleteButton);
    mainLayout->addLayout(buttonLayout);

    connect(deleteButton, &QPushButton::clicked, this, &SupprimerEnseignantWindow::onDeleteClicked);
    connect(cancelButton, &QPushButton::clicked, this, &SupprimerEnseignantWindow::onCancelClicked);

    connect(this, &SupprimerEnseignantWindow::windowClosed, this, &SupprimerEnseignantWindow::updateEnseignantComboBox);
}

SupprimerEnseignantWindow::~SupprimerEnseignantWindow() {
    emit windowClosed();
}

void SupprimerEnseignantWindow::loadTeachersFromCSV() {
    QFile file(QDir::currentPath() + "/../../CSV/" + "Enseignants.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur", "Impossible de lire le fichier Enseignant.csv.");
        return;
    }

    QTextStream in(&file);
    bool isFirstLine = true;

    teacherData.clear();

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }

        if (!line.isEmpty()) {
            QStringList fields = line.split(",");
            if (fields.size() >= 2) {
                QString nom = fields[0].trimmed();
                QString prenom = fields[1].trimmed();
                teacherData[nom].append(prenom);
            }
        }
    }
    file.close();

    nameComboBox->addItem("Sélectionner");
    nameComboBox->addItems(teacherData.keys());}

void SupprimerEnseignantWindow::updatePrenomComboBox(const QString &selectedName) {
    prenomComboBox->clear();

    if (teacherData.contains(selectedName)) {
        prenomComboBox->addItems(teacherData[selectedName]);
    }
}

void SupprimerEnseignantWindow::onDeleteClicked() {
    QString nom = nameComboBox->currentText();
    QString prenom = prenomComboBox->currentText();

    if (nom.isEmpty() || prenom.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un nom et un prénom.");
        return;
    }
    retirerEnseignantCSV(nom.toStdString(), prenom.toStdString());
    QMessageBox::information(this, "Succès", QString("L'enseignant '%1 %2' a été supprimé.").arg(nom, prenom));
    emit windowClosed();
}

void SupprimerEnseignantWindow::onCancelClicked() {
    QMessageBox::information(this, "Annulé", "Suppression annulée.");
    emit windowClosed();
    close();
}


void SupprimerEnseignantWindow::updateEnseignantComboBox() {
    nameComboBox->clear();
    prenomComboBox->clear();
    loadTeachersFromCSV();
}

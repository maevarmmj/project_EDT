#include "ajouterGroupeWindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QSpinBox>
#include <iostream>

AjouterGroupeWindow::AjouterGroupeWindow(QWidget *parent)
    : QMainWindow(parent) {

    // Définition de la taille de la fenêtre
    resize(600, 400);
    setWindowTitle("Créer un groupe");

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    setWindowModality(Qt::ApplicationModal);

    // Ajout d'un style général pour la fenêtre
    // this->setStyleSheet(
    //     "QWidget { background-color: #f4f4f4; }"
    //     "QLabel { font-size: 16px; font-weight: bold; color: #333; }"
    //     "QPushButton#saveButton { background-color: #5cb85c; color: white; font-size: 14px; padding: 8px; border-radius: 5px; }"
    //     "QPushButton#saveButton:hover { background-color: #4cae4c; }"
    //     "QPushButton#cancelButton { background-color: #d9534f; color: white; font-size: 14px; padding: 8px; border-radius: 5px; }"
    //     "QPushButton#cancelButton:hover { background-color: #c9302c; }"
    //     "QLineEdit, QComboBox { font-size: 14px; padding: 6px; border: 1px solid #ccc; border-radius: 5px; }"
    //     );

    mainLayout = new QVBoxLayout();
    centralWidget->setLayout(mainLayout);

    QLabel *titleLabel = new QLabel("Créer un élément :", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    categoryComboBox = new QComboBox(this);
    categoryComboBox->addItem("Étudiants");
    categoryComboBox->addItem("Enseignant");
    categoryComboBox->addItem("Salle");
    categoryComboBox->setStyleSheet("font-size: 14px; padding: 6px;");
    mainLayout->addWidget(categoryComboBox);

    formLayout = new QFormLayout();
    mainLayout->addLayout(formLayout);

    connect(categoryComboBox, &QComboBox::currentTextChanged, this, &AjouterGroupeWindow::onCategoryChanged);

    // Alignement des boutons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    cancelButton = new QPushButton("Annuler", this);
    cancelButton->setObjectName("cancelButton");

    saveButton = new QPushButton("Enregistrer", this);
    saveButton->setObjectName("saveButton");

    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(saveButton);
    mainLayout->addLayout(buttonLayout);

    connect(saveButton, &QPushButton::clicked, this, &AjouterGroupeWindow::onSaveClicked);
    connect(cancelButton, &QPushButton::clicked, this, &AjouterGroupeWindow::onCancelClicked);

    onCategoryChanged(categoryComboBox->currentText());
}

AjouterGroupeWindow::~AjouterGroupeWindow() {}

void AjouterGroupeWindow::onCategoryChanged(const QString &category) {
    clearForm();

    if (category == "Étudiants") {
        nameLineEdit = new QLineEdit(this);
        formLayout->addRow("Nom du groupe :", nameLineEdit);
    }
    else if (category == "Enseignant") {
        nameLineEdit = new QLineEdit(this);
        prenomLineEdit = new QLineEdit(this);
        formLayout->addRow("Nom :", nameLineEdit);
        formLayout->addRow("Prénom :", prenomLineEdit);
    }
    else if (category == "Salle") {
        salleSpinBox = new QSpinBox(this);  // Utilisation de la variable membre
        salleSpinBox->setRange(1, 438);

        typeComboBox = new QComboBox(this);
        typeComboBox->addItems({"CM", "TP Informatique", "TP Electronique", "TD", "Examen"});

        formLayout->addRow("Numéro de salle :", salleSpinBox);
        formLayout->addRow("Type :", typeComboBox);
    }
}

void AjouterGroupeWindow::clearForm() {
    while (formLayout->count() > 0) {
        QLayoutItem *item = formLayout->takeAt(0);
        if (item != nullptr) {
            delete item->widget();
            delete item;
        }
    }
}


void AjouterGroupeWindow::onSaveClicked() {
    QString category = categoryComboBox->currentText();
    QString data;

    if (category == "Étudiant") {
        data = nameLineEdit->text();
        std::cout << "Categorie Étudiant: \nNom du groupe: "
                  << data.toStdString() << std::endl;
    }
    else if (category == "Enseignant") {
        data = nameLineEdit->text() + ", " + prenomLineEdit->text();
        std::cout << "Categorie Enseignant: \nNom: "
                  << nameLineEdit->text().toStdString()
                  << ", Prenom: "
                  << prenomLineEdit->text().toStdString()
                  << std::endl;
    }
    else if (category == "Salle") {
        data = QString::number(salleSpinBox->value()) + ", " + typeComboBox->currentText();
        std::cout << "Categorie Salle: \nNumero: "
                  << salleSpinBox->value()
                  << ", Type: "
                  << typeComboBox->currentText().toStdString()
                  << std::endl;
    }

    QFile file("data.csv");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << category << "," << data << "\n";
        file.close();
        QMessageBox::information(this, "Succès", "Les données ont été enregistrées.");
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible d'écrire dans le fichier.");
    }
}

void AjouterGroupeWindow::onCancelClicked() {
    QMessageBox::information(this, "Annulé", "L'opération a été annulée.");
    close();
}

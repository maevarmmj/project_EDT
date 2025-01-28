#include "ajoutecueWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QStyleFactory>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMap>


AjoutEcueWindow::AjoutEcueWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Ajout d'ECUE");
    resize(600, 500);
    setWindowModality(Qt::ApplicationModal);

    // Appliquer un style pour rendre la fenêtre plus esthétique
    // setStyleSheet(
    //     "QWidget { background-color: #f4f4f4; }"
    //     "QLabel { font-size: 16px; font-weight: bold; color: #333; }"
    //     "QPushButton#saveButton { background-color: #5cb85c; color: white; font-size: 16px; padding: 12px; border-radius: 8px; }"
    //     "QPushButton#saveButton:hover { background-color: #4cae4c; }"
    //     "QPushButton#cancelButton { background-color: #d9534f; color: white; font-size: 16px; padding: 12px; border-radius: 8px; }"
    //     "QPushButton#cancelButton:hover { background-color: #c9302c; }"
    //     "QLineEdit, QComboBox { font-size: 14px; padding: 6px; border: 1px solid #ccc; border-radius: 5px; }"
    //     );

    // Layout principal avec marges et espacement
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    // Ligne 1 : Nom de l'ECUE
    QHBoxLayout *ecueLayout = new QHBoxLayout();
    QLabel *ecueLabel = new QLabel("Nom de l'ECUE:");
    ecueLineEdit = new QLineEdit();
    ecueLayout->addWidget(ecueLabel);
    ecueLayout->addWidget(ecueLineEdit);
    mainLayout->addLayout(ecueLayout);

    // Ligne 2 : Groupe étudiant et enseignant
    QHBoxLayout *groupTeacherLayout = new QHBoxLayout();

    QHBoxLayout *nomEnseignantLayout = new QHBoxLayout();
    QHBoxLayout *prenomEnseignantLayout = new QHBoxLayout();
    QVBoxLayout *enseignantLayout = new QVBoxLayout;

    QLabel *groupLabel = new QLabel("Groupe étudiant:");
    groupComboBox = new QComboBox();

    QLabel *nomLabel = new QLabel("Nom enseignant", this);
    nomComboBox = new QComboBox(this);
    nomComboBox->addItem("Sélectionner");

    QLabel *prenomLabel = new QLabel("Prénom enseignant", this);
    prenomComboBox = new QComboBox(this);


    loadTeachersFromCSV();
    loadGroupsFromCSV();

    groupTeacherLayout->addWidget(groupLabel);
    groupTeacherLayout->addWidget(groupComboBox);
    groupTeacherLayout->addSpacing(20);

    nomEnseignantLayout->addWidget(nomLabel);
    nomEnseignantLayout->addWidget(nomComboBox);

    prenomEnseignantLayout->addWidget(prenomLabel);
    prenomEnseignantLayout->addWidget(prenomComboBox);

    enseignantLayout->addLayout(nomEnseignantLayout);
    enseignantLayout->addLayout(prenomEnseignantLayout);


    groupTeacherLayout->addLayout(enseignantLayout);

    mainLayout->addLayout(groupTeacherLayout);

    // Ligne 3 : Type de cours
    QGroupBox *typeGroupBox = new QGroupBox("Type de cours");
    QVBoxLayout *typeCourseLayout = new QVBoxLayout();
    typeCourseLayout->setSpacing(10);

    QHBoxLayout *cmLayout = new QHBoxLayout();
    cmCheckBox = new QCheckBox("CM");
    cmSpinBox = new QSpinBox();
    cmSpinBox->setRange(0, 100);
    cmSpinBox->setSuffix(" h");
    cmSpinBox->setValue(0);
    cmSpinBox->setVisible(false);
    cmLayout->addWidget(cmCheckBox);
    cmLayout->addWidget(cmSpinBox);
    typeCourseLayout->addLayout(cmLayout);

    QHBoxLayout *tpLayout = new QHBoxLayout();
    tpCheckBox = new QCheckBox("TP");
    tpLayout->addWidget(tpCheckBox);
    typeCourseLayout->addLayout(tpLayout);

    QHBoxLayout *elecLayout = new QHBoxLayout();
    elecCheckBox = new QCheckBox("Elec");
    elecCheckBox->setVisible(false);
    elecSpinBox = new QSpinBox();
    elecSpinBox->setRange(0, 100);
    elecSpinBox->setSuffix(" h");
    elecSpinBox->setValue(0);
    elecSpinBox->setVisible(false);
    QSpacerItem *elecSpacer = new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);
    elecLayout->addItem(elecSpacer);
    elecLayout->addWidget(elecCheckBox);
    elecLayout->addWidget(elecSpinBox);
    typeCourseLayout->addLayout(elecLayout);

    QHBoxLayout *infoLayout = new QHBoxLayout();
    infoCheckBox = new QCheckBox("Info");
    infoCheckBox->setVisible(false);
    infoSpinBox = new QSpinBox();
    infoSpinBox->setRange(0, 100);
    infoSpinBox->setSuffix(" h");
    infoSpinBox->setValue(0);
    infoSpinBox->setVisible(false);
    QSpacerItem *infoSpacer = new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);
    infoLayout->addItem(infoSpacer);
    infoLayout->addWidget(infoCheckBox);
    infoLayout->addWidget(infoSpinBox);
    typeCourseLayout->addLayout(infoLayout);

    QHBoxLayout *tdLayout = new QHBoxLayout();
    tdCheckBox = new QCheckBox("TD");
    tdSpinBox = new QSpinBox();
    tdSpinBox->setRange(0, 100);
    tdSpinBox->setSuffix(" h");
    tdSpinBox->setValue(0);
    tdSpinBox->setVisible(false);
    tdLayout->addWidget(tdCheckBox);
    tdLayout->addWidget(tdSpinBox);
    typeCourseLayout->addLayout(tdLayout);

    QHBoxLayout *examLayout = new QHBoxLayout();
    examCheckBox = new QCheckBox("Examen");
    examSpinBox = new QSpinBox();
    examSpinBox->setRange(0, 100);
    examSpinBox->setSuffix(" h");
    examSpinBox->setValue(0);
    examSpinBox->setVisible(false);
    examLayout->addWidget(examCheckBox);
    examLayout->addWidget(examSpinBox);
    typeCourseLayout->addLayout(examLayout);


    typeGroupBox->setLayout(typeCourseLayout);
    mainLayout->addWidget(typeGroupBox);

    // Connecter les cases à cocher pour afficher/masquer les champs de saisie
    connect(cmCheckBox, &QCheckBox::checkStateChanged, this, &AjoutEcueWindow::toggleCM);
    connect(tpCheckBox, &QCheckBox::checkStateChanged, this, &AjoutEcueWindow::toggleTP);
    connect(elecCheckBox, &QCheckBox::checkStateChanged, this, &AjoutEcueWindow::toggleElec);
    connect(infoCheckBox, &QCheckBox::checkStateChanged, this, &AjoutEcueWindow::toggleInfo);
    connect(tdCheckBox, &QCheckBox::checkStateChanged, this, &AjoutEcueWindow::toggleTD);
    connect(examCheckBox, &QCheckBox::checkStateChanged, this, &AjoutEcueWindow::toggleExam);
    connect(nomComboBox, &QComboBox::currentTextChanged, this, &AjoutEcueWindow::updatePrenoms);


    // Ligne 4 : Boutons Enregistrer et Annuler
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->setSpacing(20);

    // Boutons Annuler et Enregistrer
    QPushButton *cancelButton = new QPushButton("Annuler");
    QPushButton *saveButton = new QPushButton("Enregistrer");

    // Donner des IDs pour le style personnalisé
    cancelButton->setObjectName("cancelButton");
    saveButton->setObjectName("saveButton");

    buttonsLayout->addStretch();
    buttonsLayout->addWidget(cancelButton); // Bouton Annuler à gauche
    buttonsLayout->addWidget(saveButton);   // Bouton Enregistrer à droite
    buttonsLayout->addStretch();
    mainLayout->addLayout(buttonsLayout);

    // Connecter les boutons
    connect(saveButton, &QPushButton::clicked, this, &AjoutEcueWindow::enregistrer);
    connect(cancelButton, &QPushButton::clicked, this, &AjoutEcueWindow::annuler);

    // Appliquer le layout principal à la fenêtre
    setLayout(mainLayout);
}

void AjoutEcueWindow::toggleCM(int state) {
    cmSpinBox->setVisible(state == Qt::Checked);
}

void AjoutEcueWindow::toggleTP(int state) {
    bool visible = (state == Qt::Checked);
    elecCheckBox->setVisible(visible);
    infoCheckBox->setVisible(visible);
}

void AjoutEcueWindow::toggleElec(int state) {
    elecSpinBox->setVisible(state == Qt::Checked);
}

void AjoutEcueWindow::toggleInfo(int state) {
    infoSpinBox->setVisible(state == Qt::Checked);
}

void AjoutEcueWindow::loadTeachersFromCSV() {
    QFile file(QDir::currentPath() + "/../../CSV/" + "Enseignants.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible de lire le fichier Enseignants.csv.");
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
            if (fields.size() >= 2) {
                QString nom = fields[0].trimmed();
                QString prenom = fields[1].trimmed();

                // Ajoutez le prénom à la liste des prénoms associée au nom
                enseignantsData[nom].append(prenom);
            }
        }
    }

    file.close();

    // Remplissez la combobox des noms avec les clés de la map
    nomComboBox->addItems(enseignantsData.keys());
}

void AjoutEcueWindow::updatePrenoms(const QString &nom) {
    prenomComboBox->clear(); // Effacez les prénoms existants

    // Ajoutez les prénoms correspondants au nom sélectionné
    if (enseignantsData.contains(nom)) {
        prenomComboBox->addItems(enseignantsData[nom]);
    }
}


void AjoutEcueWindow::toggleTD(int state) {
    tdSpinBox->setVisible(state == Qt::Checked);
}

void AjoutEcueWindow::toggleExam(int state) {
    examSpinBox->setVisible(state == Qt::Checked);
}

void AjoutEcueWindow::annuler() {
    ecueLineEdit->clear();
    nomComboBox ->clear();
    prenomComboBox  ->clear();
    groupComboBox->setCurrentIndex(0);
    cmCheckBox->setChecked(false);
    tpCheckBox->setChecked(false);
    tdCheckBox->setChecked(false);
    examCheckBox->setChecked(false);
    elecCheckBox->setChecked(false);
    infoCheckBox->setChecked(false);

    QMessageBox::information(this, "Opération annulée", "L'opération a été annulée.");

    close();
}

void AjoutEcueWindow::enregistrer() {
    // Vérification du nom de l'ECUE
    if (ecueLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez renseigner le nom de l'ECUE.");
        return;
    }

    // Vérification si un enseignant est sélectionné
    if (nomComboBox ->currentIndex() == 0 && prenomComboBox->currentIndex() == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un enseignant.");
        return;
    }

    // Vérification si au moins un type de cours a été coché
    if (!cmCheckBox->isChecked() && !tpCheckBox->isChecked() && !tdCheckBox->isChecked() &&
        !examCheckBox->isChecked() && !elecCheckBox->isChecked() && !infoCheckBox->isChecked()) {
        QMessageBox::warning(this, "Erreur", "Veuillez cocher au moins un type de cours.");
        return;
    }



    // Vérification des heures renseignées pour les types de cours
    if (cmCheckBox->isChecked() && cmSpinBox->value() == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez renseigner des heures pour le CM.");
        return;
    }
    if (tpCheckBox->isChecked() && (elecSpinBox->value() == 0 && infoSpinBox->value() == 0)) {
        QMessageBox::warning(this, "Erreur", "Veuillez renseigner des heures pour le TP.");
        return;
    }
    if (tdCheckBox->isChecked() && tdSpinBox->value() == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez renseigner des heures pour le TD.");
        return;
    }
    if (examCheckBox->isChecked() && examSpinBox->value() == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez renseigner des heures pour l'Examen.");
        return;
    }


    QString message = QString("Nom de l'ECUE: %1, Groupe étudiant: %2, Enseignant: %3 %4, ")
                          .arg(ecueLineEdit->text())
                          .arg(groupComboBox->currentText())
                          .arg(nomComboBox->currentText())
                          .arg(prenomComboBox->currentText());


    std::vector<cours> typesCours = {};
    std::vector<int> heuresCours = {};
    EcueControleur ecue;


    if (cmCheckBox->isChecked()){
        message += QString("CM: %1 heures ").arg(cmSpinBox->value());
        typesCours.push_back(CM);
        heuresCours.push_back(cmSpinBox->value());
    }
    if (tpCheckBox->isChecked()) {
        if (elecCheckBox->isChecked()) {
                message += QString("TP Elec : %1 heures ").arg(elecSpinBox->value());
                typesCours.push_back(TP_ELEC);
                heuresCours.push_back(elecSpinBox->value());        }
        if (infoCheckBox->isChecked()) {
                message += QString("TP Info : %1 heures ").arg(infoSpinBox->value());
                typesCours.push_back(TP_INFO);
                heuresCours.push_back(infoSpinBox->value());
                 }
    }
    if (tdCheckBox->isChecked()){
        message += QString("TD: %1 heures ").arg(tdSpinBox->value());
        typesCours.push_back(TD);
        heuresCours.push_back(tdSpinBox->value());
    }
    if (examCheckBox->isChecked()){
        message += QString("Examen: %1 heures ").arg(examSpinBox->value());
        typesCours.push_back(EXAMEN);
        heuresCours.push_back(examSpinBox->value());
    }

    ecue.creerECUE(ecueLineEdit->text().toStdString(), nomComboBox->currentText().toStdString(), prenomComboBox->currentText().toStdString(), typesCours, heuresCours, groupComboBox->currentText().toStdString());

    // Afficher dans la console
    qDebug() << "Données sauvegardées :\n" << message;

    // Confirmation à l'utilisateur
    QMessageBox::information(this, "Données sauvegardées", "Les données ont été sauvegardées avec succès !");
}

void AjoutEcueWindow::loadGroupsFromCSV() {
    QFile file(QDir::currentPath() + "/../../CSV/" + "Groupes.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible de lire le fichier Groupes.csv.");
        return;
    }

    QTextStream in(&file);
    bool isFirstLine = true;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        if (isFirstLine) {
            isFirstLine = false;
            continue; // Ignorer l'en-tête
        }

        if (!line.isEmpty()) {
            groupComboBox->addItem(line);
        }
    }

    file.close();
}

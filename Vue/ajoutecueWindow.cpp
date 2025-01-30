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
#include <QStackedWidget>
#include <QTimer>



AjoutEcueWindow::AjoutEcueWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Ajout d'ECUE");
    resize(600, 500);
    setWindowModality(Qt::ApplicationModal);
    QString file(QDir::currentPath() + "/../../Ressources/planning.ico");
    QIcon icon(file);
    setWindowIcon(icon);


    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    QHBoxLayout *ecueLayout = new QHBoxLayout();
    QLabel *ecueLabel = new QLabel("Nom de l'ECUE:");
    ecueLineEdit = new QLineEdit();
    ecueLayout->addWidget(ecueLabel);
    ecueLayout->addWidget(ecueLineEdit);
    mainLayout->addLayout(ecueLayout);

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


    // ------------------ Messages si réussite / erreur de la tache ------------------------

    QStackedWidget *messageStack = new QStackedWidget(this);


    QLabel *AJOUT_REUSSI = new QLabel("Ajout réussi !");
    AJOUT_REUSSI->setAlignment(Qt::AlignCenter);
    AJOUT_REUSSI->setStyleSheet("font-size: 14px; color: green; font-weight: bold;");

    QLabel *MANQUE_INFO = new QLabel("Veuillez remplir toutes les informations !");
    MANQUE_INFO->setAlignment(Qt::AlignCenter);
    MANQUE_INFO->setStyleSheet("font-size: 14px; color: red; font-weight: bold;");

    QLabel *EXISTE_DEJA = new QLabel("Cette ECUE existe déjà !");
    EXISTE_DEJA->setAlignment(Qt::AlignCenter);
    EXISTE_DEJA->setStyleSheet("font-size: 14px; color: red; font-weight: bold;");

    QLabel *ERREUR_PROF = new QLabel("Une ECUE ne peut être associé qu'à un enseignant par groupe !");
    ERREUR_PROF->setAlignment(Qt::AlignCenter);
    ERREUR_PROF->setStyleSheet("font-size: 14px; color: red; font-weight: bold;");

    AJOUT_REUSSI->setFixedHeight(30);
    MANQUE_INFO->setFixedHeight(30);
    EXISTE_DEJA->setFixedHeight(30);
    ERREUR_PROF->setFixedHeight(30);

    messageStack->addWidget(AJOUT_REUSSI);
    messageStack->addWidget(MANQUE_INFO);
    messageStack->addWidget(EXISTE_DEJA);
    messageStack->addWidget(ERREUR_PROF);


    AJOUT_REUSSI->hide();
    MANQUE_INFO->hide();
    EXISTE_DEJA->hide();
    ERREUR_PROF->hide();

    // ------------------ Messages si réussite / erreur de la tache ------------------------


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

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->setSpacing(20);

    QPushButton *cancelButton = new QPushButton("Annuler");
    QPushButton *saveButton = new QPushButton("Enregistrer");

    cancelButton->setObjectName("cancelButton");
    saveButton->setObjectName("saveButton");

    buttonsLayout->addStretch();
    buttonsLayout->addWidget(cancelButton);
    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addStretch();
    mainLayout->addWidget(messageStack);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);

    // ---- Connexion de chaque bouton et leurs actions ----

    connect(cmCheckBox, &QCheckBox::checkStateChanged, this, &AjoutEcueWindow::toggleCM);
    connect(tpCheckBox, &QCheckBox::checkStateChanged, this, &AjoutEcueWindow::toggleTP);
    connect(elecCheckBox, &QCheckBox::checkStateChanged, this, &AjoutEcueWindow::toggleElec);
    connect(infoCheckBox, &QCheckBox::checkStateChanged, this, &AjoutEcueWindow::toggleInfo);
    connect(tdCheckBox, &QCheckBox::checkStateChanged, this, &AjoutEcueWindow::toggleTD);
    connect(examCheckBox, &QCheckBox::checkStateChanged, this, &AjoutEcueWindow::toggleExam);
    connect(nomComboBox, &QComboBox::currentTextChanged, this, &AjoutEcueWindow::updatePrenoms);
    connect(saveButton, &QPushButton::clicked, this, &AjoutEcueWindow::enregistrer);
    connect(cancelButton, &QPushButton::clicked, this, &AjoutEcueWindow::annuler);

}

// ---- Fermer la fenêtre à partir de la croix ----

AjoutEcueWindow::~AjoutEcueWindow(){
    emit windowClosed();
}

// ---- Faire afficher le spinbox CM après clic sur la checkbox CM ----

void AjoutEcueWindow::toggleCM(int state) {
    cmSpinBox->setVisible(state == Qt::Checked);
}

// ---- Faire afficher les checkbox Elec et Info après clic sur la checkbox TP ----

void AjoutEcueWindow::toggleTP(int state) {
    bool visible = (state == Qt::Checked);
    elecCheckBox->setVisible(visible);
    infoCheckBox->setVisible(visible);

    if (!visible) {
        elecSpinBox->setVisible(false);
        infoSpinBox->setVisible(false);
        elecCheckBox->setChecked(false);
        infoCheckBox->setChecked(false);
    }
}

// ---- Faire afficher le spinbox Elec après clic sur la checkbox Elec ----

void AjoutEcueWindow::toggleElec(int state) {
    elecSpinBox->setVisible(state == Qt::Checked);
}

// ---- Faire afficher le spinbox Info après clic sur la checkbox Info ----

void AjoutEcueWindow::toggleInfo(int state) {
    infoSpinBox->setVisible(state == Qt::Checked);
}




// ---- MAJ des prénoms après avoir renseigné le nom de famille  ----

void AjoutEcueWindow::updatePrenoms(const QString &nom) {
    prenomComboBox->clear(); // Effacez les prénoms existants

    // Ajoutez les prénoms correspondants au nom sélectionné
    if (enseignantsData.contains(nom)) {
        prenomComboBox->addItems(enseignantsData[nom]);
    }
}

// ---- Faire afficher le spinbox TD après clic sur la checkbox TD ----

void AjoutEcueWindow::toggleTD(int state) {
    tdSpinBox->setVisible(state == Qt::Checked);
}

// ---- Faire afficher le spinbox examen après clic sur la checkbox Examen  ----

void AjoutEcueWindow::toggleExam(int state) {
    examSpinBox->setVisible(state == Qt::Checked);
}


// ---- Charger Enseignants.csv ----

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


// ---- Charger Groupes.csv ----

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
            continue;
        }

        if (!line.isEmpty()) {
            groupComboBox->addItem(line);
        }
    }

    file.close();
}


// ---- Quand on clique sur le bouton "Enregistrer" ----

void AjoutEcueWindow::enregistrer() {
    QStackedWidget* messageStack = findChild<QStackedWidget*>();
    if (!messageStack) return;

    // Fonction pour afficher un message et lancer le timer
    auto showMessageAndHide = [ messageStack](int index) {
        messageStack->setCurrentIndex(index);
        for (int i = 0; i < messageStack->count(); ++i) {
            QWidget* widget = messageStack->widget(i);
            if (widget) {
                if (i == index) {
                    widget->show();
                } else {
                    widget->hide();
                }
            }
        }

        QTimer::singleShot(2000, [messageStack]() {
            if (messageStack) {
                for (int i = 0; i < messageStack->count(); ++i) {
                    QWidget* widget = messageStack->widget(i);
                    if (widget) {
                        widget->hide();
                    }
                }
            }
        });
    };

    // Vérification du nom de l'ECUE
    if (ecueLineEdit->text().isEmpty()) {
        showMessageAndHide(1); // Index de MANQUE_INFO
        return;
    }

    // Vérification si un enseignant est sélectionné
    if (nomComboBox->currentIndex() == 0 && prenomComboBox->currentIndex() == 0) {
        showMessageAndHide(1); // Index de MANQUE_INFO
        return;
    }

    // Vérification si au moins un type de cours a été coché
    if (!cmCheckBox->isChecked() && !tpCheckBox->isChecked() && !tdCheckBox->isChecked() &&
        !examCheckBox->isChecked() && !elecCheckBox->isChecked() && !infoCheckBox->isChecked()) {
        showMessageAndHide(1); // Index de MANQUE_INFO
        return;
    }

    // Vérification des heures renseignées pour les types de cours
    if (cmCheckBox->isChecked() && cmSpinBox->value() == 0) {
        showMessageAndHide(1); // Index de MANQUE_INFO
        return;
    }
    if (tpCheckBox->isChecked() && (elecSpinBox->value() == 0 && infoSpinBox->value() == 0)) {
        showMessageAndHide(1); // Index de MANQUE_INFO
        return;
    }
    if (tdCheckBox->isChecked() && tdSpinBox->value() == 0) {
        showMessageAndHide(1); // Index de MANQUE_INFO
        return;
    }
    if (examCheckBox->isChecked() && examSpinBox->value() == 0) {
        showMessageAndHide(1); // Index de MANQUE_INFO
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


    // Appel de la fonction creerECUE et gestion du résultat
    CreationResult result = ecue.creerECUE(ecueLineEdit->text().toStdString(), nomComboBox->currentText().toStdString(), prenomComboBox->currentText().toStdString(), typesCours, heuresCours, groupComboBox->currentText().toStdString());

    // Afficher dans la console
    qDebug() << "Données sauvegardées :\n" << message;

    if (result == CreationResult::Success) {
        showMessageAndHide(0); // 0 pour AJOUT_REUSSI
    } else if (result == CreationResult::AlreadyExists) {
        showMessageAndHide(2); // 3 pour EXISTE_DEJA
    } else if (result == CreationResult::Error) {
        showMessageAndHide(3);
    }
    emit windowClosed();
}

// ---- Quand on clique sur le bouton "annuler" ----

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

    emit windowClosed();

    close();
}

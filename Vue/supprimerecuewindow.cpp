#include "supprimerecuewindow.h"

SupprimerEcueWindow::SupprimerEcueWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Supprimer une ECUE");
    resize(400, 300);
    setWindowModality(Qt::ApplicationModal);
    QString file(QDir::currentPath() + "/../../Ressources/planning.ico");
    QIcon icon(file);
    setWindowIcon(icon);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    ecueComboBox = new QComboBox();
    enseignantNomComboBox = new QComboBox();
    enseignantPrenomComboBox = new QComboBox();
    groupeComboBox = new QComboBox();

    ecueComboBox->addItem("Sélectionner");

    chargerEcueDepuisCSV();

    // ------------------ Messages si réussite / erreur de la tache ------------------------

    QStackedWidget *messageStack = new QStackedWidget(this);

    QLabel *SUPPRESSION_REUSSIE = new QLabel("Suppression réussie !");
    SUPPRESSION_REUSSIE->setAlignment(Qt::AlignCenter);
    SUPPRESSION_REUSSIE->setObjectName("reussi");

    QLabel *MANQUE_INFO = new QLabel("Veuillez remplir toutes les informations !");
    MANQUE_INFO->setAlignment(Qt::AlignCenter);
    MANQUE_INFO->setObjectName("loupe");

    SUPPRESSION_REUSSIE->setFixedHeight(30);
    MANQUE_INFO->setFixedHeight(30);

    messageStack->addWidget(SUPPRESSION_REUSSIE);
    messageStack->addWidget(MANQUE_INFO);

    SUPPRESSION_REUSSIE->hide();
    MANQUE_INFO->hide();

    // ------------------ Messages si réussite / erreur de la tache ------------------------


    QLabel *label = new QLabel("Insérez de l'information de l'ECUE à supprimer");
    label->setAlignment(Qt::AlignHCenter);
    label->setObjectName("titleLabel");

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
    cancelButton->setObjectName("saveButton");
    deleteButton->setObjectName("cancelButton");

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addWidget(label);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(messageStack);
    mainLayout->addLayout(buttonLayout);

    connect(ecueComboBox, &QComboBox::currentTextChanged, this, &SupprimerEcueWindow::onEcueSelectionChanged);
    connect(enseignantNomComboBox, &QComboBox::currentTextChanged, this, &SupprimerEcueWindow::onEnseignantNomChanged);
    connect(enseignantPrenomComboBox, &QComboBox::currentTextChanged, this, &SupprimerEcueWindow::onEnseignantPrenomChanged);
    connect(groupeComboBox, &QComboBox::currentTextChanged, this, &SupprimerEcueWindow::onGroupeChanged);

    connect(deleteButton, &QPushButton::clicked, this, &SupprimerEcueWindow::onSupprimerClicked);
    connect(cancelButton, &QPushButton::clicked, this, &SupprimerEcueWindow::onAnnulerClicked);

    connect(this, &SupprimerEcueWindow::ecueWindowClosed, this, &SupprimerEcueWindow::updateEcueComboBoxes);
}

// ---- Fermer la fenêtre à partir de la croix ----

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

// ---- Changement des informations des comboBox selon la sélection de l'ECUE (en cascade) ----

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

// ---- Changement des informations des comboBox selon la sélection du nom de l'Enseignant (en cascade) ----

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

// ---- Changement des informations des comboBox selon la sélection du prénom de l'Enseignant (en cascade) ----

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

// ---- Changement des informations des comboBox selon la sélection du Groupe (en cascade) ----

void SupprimerEcueWindow::onGroupeChanged(const QString &groupe) {
    if (groupe == "Sélectionner") return;

    QString ecue = ecueComboBox->currentText();
    QString nom = enseignantNomComboBox->currentText();
    QString prenom = enseignantPrenomComboBox->currentText();

    qDebug() << "Groupe sélectionné :" << groupe;
    qDebug() << "ECUE :" << ecue << ", Nom :" << nom << ", Prénom :" << prenom;
}


// ---- Cascade des changements d'informations selon ce qui a été sélectionné ----

void SupprimerEcueWindow::updateEcueComboBoxes() {
    ecueComboBox->clear();
    enseignantNomComboBox->clear();
    enseignantPrenomComboBox->clear();
    groupeComboBox->clear();

    ecueComboBox->addItem("Sélectionner");

    chargerEcueDepuisCSV();
}

// ---- Quand on clique sur le bouton "Supprimer" ----

void SupprimerEcueWindow::onSupprimerClicked()
{
    QStackedWidget* messageStack = findChild<QStackedWidget*>();
    if (!messageStack) return;


    auto showMessageAndHide = [messageStack](int index) {
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

    QString ecueName = ecueComboBox->currentText();
    QString enseignantNom = enseignantNomComboBox->currentText();
    QString enseignantPrenom = enseignantPrenomComboBox->currentText();
    QString groupe = groupeComboBox->currentText();

    if (ecueName.isEmpty() || enseignantNom.isEmpty() || enseignantPrenom.isEmpty() || groupe.isEmpty()) {
        showMessageAndHide(1); // 1 pour MANQUE_INFO
        return;
    }

    SuppressionResult result = ecue.retirerECUECSV(ecueName.toStdString(), enseignantNom.toStdString(), enseignantPrenom.toStdString(), groupe.toStdString());

    if (result == SuppressionResult::Success) {
        showMessageAndHide(0); // 0 pour SUPPRESSION_REUSSIE
    } else {
        showMessageAndHide(1); // 1 pour MANQUE_INFO
    }

    emit ecueWindowClosed();
}


// ---- Quand on clique sur le bouton "annuler" ----

void SupprimerEcueWindow::onAnnulerClicked() {
    emit ecueWindowClosed();
    close();
}

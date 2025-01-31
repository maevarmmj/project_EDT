#include "supprimerGroupeWindow.h"

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

    // ------------------ Messages si réussite / erreur de la tache ------------------------

    QStackedWidget *messageStack = new QStackedWidget(this);

    QLabel *SUPPRESSION_REUSSIE = new QLabel("Suppression réussie !");
    SUPPRESSION_REUSSIE->setAlignment(Qt::AlignCenter);
    SUPPRESSION_REUSSIE->setStyleSheet("font-size: 14px; color: green; font-weight: bold;");

    QLabel *MANQUE_INFO = new QLabel("Veuillez remplir toutes les informations !");
    MANQUE_INFO->setAlignment(Qt::AlignCenter);
    MANQUE_INFO->setStyleSheet("font-size: 14px; color: red; font-weight: bold;");

    SUPPRESSION_REUSSIE->setFixedHeight(30);
    MANQUE_INFO->setFixedHeight(30);

    messageStack->addWidget(SUPPRESSION_REUSSIE);
    messageStack->addWidget(MANQUE_INFO);

    SUPPRESSION_REUSSIE->hide();
    MANQUE_INFO->hide();

    // ------------------ Messages si réussite / erreur de la tache ------------------------


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
    mainLayout->addWidget(messageStack);
    mainLayout->addLayout(buttonLayout);

    connect(deleteButton, &QPushButton::clicked, this, &SupprimerGroupeWindow::onDeleteClicked);
    connect(cancelButton, &QPushButton::clicked, this, &SupprimerGroupeWindow::onCancelClicked);

        connect(this, &SupprimerGroupeWindow::windowClosed, this, &SupprimerGroupeWindow::updateGroupComboBox);
}

// ---- Fermer la fenêtre à partir de la croix ----

SupprimerGroupeWindow::~SupprimerGroupeWindow() {
    emit windowClosed();
}

// ---- Chargement de Groupes.csv ----

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


// ---- MAJ de Groupes.csv après suppression ----

void SupprimerGroupeWindow::updateGroupComboBox() {
    groupComboBox->clear();
    loadGroupsFromCSV();
}


// ---- Quand on clique sur le bouton "Supprimer" ----
void SupprimerGroupeWindow::onDeleteClicked() {
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

    QString selectedGroup = groupComboBox->currentText();

    if (selectedGroup.isEmpty()) {
        showMessageAndHide(1); // 1 pour MANQUE_INFO
        return;
    }

    SuppressionResult result = retirerGroupeEtudiantCSV(selectedGroup.toStdString());
    if (result == SuppressionResult::Success) {
        showMessageAndHide(0); // 0 pour SUPPRESSION_REUSSIE
    } else {
        showMessageAndHide(1); // 1 pour MANQUE_INFO
    }
    emit windowClosed();
}

// ---- Quand on clique sur le bouton "annuler" ----
void SupprimerGroupeWindow::onCancelClicked() {
    close();
}

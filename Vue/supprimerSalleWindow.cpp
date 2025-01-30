#include "supprimerSalleWindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTimer>
#include <QStackedWidget>


SupprimerSalleWindow::SupprimerSalleWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Supprimer un numéro de salle");
    resize(400, 200);
    setWindowModality(Qt::ApplicationModal);
    QString file(QDir::currentPath() + "/../../Ressources/planning.ico");
    QIcon icon(file);
    setWindowIcon(icon);

    QVBoxLayout *mainLayout = new QVBoxLayout();

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
    mainLayout->addWidget(messageStack);
    mainLayout->addLayout(buttonLayout);

    connect(annulerButton, &QPushButton::clicked, this, &SupprimerSalleWindow::annuler);
    connect(supprimerButton, &QPushButton::clicked, this, &SupprimerSalleWindow::supprimer);

    connect(this, &SupprimerSalleWindow::salleWindowClosed, this, &SupprimerSalleWindow::updateSalleComboBox);

    setLayout(mainLayout);
}

// ---- Fermer la fenêtre à partir de la croix ----

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

// ---- Quand on clique sur le bouton "Supprimer" ----
void SupprimerSalleWindow::supprimer() {
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

    QString salleNumber = salleComboBox->currentText();
    if (salleNumber.isEmpty()) {
        showMessageAndHide(1); // 1 pour MANQUE_INFO
        return;
    }
    SuppressionResult result = retirerSalleCSV(salleComboBox->currentText().toInt());
    if (result == SuppressionResult::Success) {
        showMessageAndHide(0); // 0 pour SUPPRESSION_REUSSIE
    } else {
        showMessageAndHide(1); // 1 pour MANQUE_INFO
    }
    emit salleWindowClosed();
}

// ---- Quand on clique sur le bouton "annuler" ----
void SupprimerSalleWindow::annuler() {
    emit salleWindowClosed();
    close();
}

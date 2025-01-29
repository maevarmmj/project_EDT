#include "supprimerEnseignantWindow.h"


SupprimerEnseignantWindow::SupprimerEnseignantWindow(QWidget *parent)
    : QMainWindow(parent) {

    resize(600, 300);
    setWindowTitle("Supprimer un enseignant");
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
    mainLayout->addWidget(messageStack);
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


    QString nom = nameComboBox->currentText();
    QString prenom = prenomComboBox->currentText();

    if (nom.isEmpty() || prenom.isEmpty()) {
        showMessageAndHide(1); // 1 pour MANQUE_INFO
        return;
    }
    SuppressionResult result = retirerEnseignantCSV(nom.toStdString(), prenom.toStdString());
    if (result == SuppressionResult::Success) {
        showMessageAndHide(0); // 0 pour SUPPRESSION_REUSSIE
    } else {
        showMessageAndHide(1); // 1 pour MANQUE_INFO
    }
    emit windowClosed();
}

void SupprimerEnseignantWindow::onCancelClicked() {
    close();
}


void SupprimerEnseignantWindow::updateEnseignantComboBox() {
    nameComboBox->clear();
    prenomComboBox->clear();
    loadTeachersFromCSV();
}

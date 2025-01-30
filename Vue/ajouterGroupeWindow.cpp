#include "ajouterGroupeWindow.h"

AjouterGroupeWindow::AjouterGroupeWindow(QWidget *parent)
    : QMainWindow(parent) {

    // Définition de la taille de la fenêtre
    resize(600, 400);
    setWindowTitle("Créer un élément");
    QString file(QDir::currentPath() + "/../../Ressources/planning.ico");
    QIcon icon(file);
    setWindowIcon(icon);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    setWindowModality(Qt::ApplicationModal);

    // ------------------ Messages si réussite / erreur de la tache ------------------------

    QStackedWidget *messageStack = new QStackedWidget(this);


    QLabel *AJOUT_REUSSI = new QLabel("Ajout réussi !");
    AJOUT_REUSSI->setAlignment(Qt::AlignCenter);
    AJOUT_REUSSI->setStyleSheet("font-size: 14px; color: green; font-weight: bold;");

    QLabel *MANQUE_INFO = new QLabel("Veuillez remplir toutes les informations !");
    MANQUE_INFO->setAlignment(Qt::AlignCenter);
    MANQUE_INFO->setStyleSheet("font-size: 14px; color: red; font-weight: bold;");

    QLabel *EXISTE_DEJA = new QLabel("Cette information existe déjà !");
    EXISTE_DEJA->setAlignment(Qt::AlignCenter);
    EXISTE_DEJA->setStyleSheet("font-size: 14px; color: red; font-weight: bold;");

    AJOUT_REUSSI->setFixedHeight(30);
    MANQUE_INFO->setFixedHeight(30);
    EXISTE_DEJA->setFixedHeight(30);

    messageStack->addWidget(AJOUT_REUSSI);
    messageStack->addWidget(MANQUE_INFO);
    messageStack->addWidget(EXISTE_DEJA);

    AJOUT_REUSSI->hide();
    MANQUE_INFO->hide();
    EXISTE_DEJA->hide();

    // ------------------ Messages si réussite / erreur de la tache ------------------------


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
    mainLayout->addWidget(messageStack);
    mainLayout->addLayout(buttonLayout);
    connect(saveButton, &QPushButton::clicked, this, &AjouterGroupeWindow::onSaveClicked);
    connect(cancelButton, &QPushButton::clicked, this, &AjouterGroupeWindow::onCancelClicked);

    onCategoryChanged(categoryComboBox->currentText());
}

// ---- Fermer la fenêtre à partir de la croix ----

AjouterGroupeWindow::~AjouterGroupeWindow() {
    emit windowClosed(); // Émettre le signal si la fenêtre est fermée par la croix

}

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

// ---- Quand on clique sur le bouton "Enregistrer" ----
void AjouterGroupeWindow::onSaveClicked() {
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

    QString category = categoryComboBox->currentText();
    QString data;
    CreationResult result;

    if (category == "Étudiants") {
        data = nameLineEdit->text();
        if (data.isEmpty()) {
            showMessageAndHide(1); // 2 pour MANQUE_INFO
            return;
        }
        std::cout << "Categorie Étudiant: \nNom du groupe: " << data.toStdString() << std::endl;
        result = ajouterGroupeEtudiantCSV(data.toStdString());
    }
    else if (category == "Enseignant") {
        QString nom = nameLineEdit->text();
        QString prenom = prenomLineEdit->text();
        if (nom.isEmpty() || prenom.isEmpty()) {
            showMessageAndHide(1); // 2 pour MANQUE_INFO
            return;
        }
        data = nom + ", " + prenom;
        std::cout << "Categorie Enseignant: \nNom: " << nom.toStdString() << ", Prenom: " << prenom.toStdString() << std::endl;
        result = ajouterEnseignantCSV(nom.toStdString(), prenom.toStdString());
    }
    else {
        QString type = typeComboBox->currentText();
        if (type.isEmpty()) {
            showMessageAndHide(1);
            return;
        }
        QString numero = QString::number(salleSpinBox->value());

        std::string type_str = type.toStdString();
        std::cout << "Categorie Salle: \nNumero: " << salleSpinBox->value() << ", Type: " << type.toStdString() << std::endl;
        result = ajouterSalleCSV(salleSpinBox->value(), StrToCours(type_str));
    }

    if (result == CreationResult::Success) {
        showMessageAndHide(0); // 0 pour AJOUT_REUSSI
    } else if (result == CreationResult::AlreadyExists) {
        showMessageAndHide(2); // 3 pour EXISTE_DEJA
    } else if (category != "Salle"){
        showMessageAndHide(1); // 2 pour MANQUE_INFO
    }
    emit windowClosed();
}

// ---- Quand on clique sur le bouton "annuler" ----
void AjouterGroupeWindow::onCancelClicked() {
    emit windowClosed();
    close();
}



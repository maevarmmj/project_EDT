#include "popupEdt.h"

popupEdt::popupEdt(QWidget *parent) : QMainWindow(parent) {
    this->setFixedSize(750, 350);
    // Initialize the database
    initDatabase(db);

    // Fenêtre principale
    this->setWindowTitle("Matrice de Boutons");

    // Widget central
    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    // Layout principal
    mainLayout = new QVBoxLayout(centralWidget);

    // ---------------- Bandeau du Haut --------------------
    bandeauWidget = new QWidget(centralWidget);
    bandeauLayout = new QHBoxLayout(bandeauWidget);

    // Label et SpinBox pour la semaine
    semaineLabel = new QLabel("Semaine:", bandeauWidget);
    semaineSpinBox = new QSpinBox(bandeauWidget);
    semaineSpinBox->setRange(1, 52);
    bandeauLayout->addWidget(semaineLabel);
    bandeauLayout->addWidget(semaineSpinBox);

    // Label et ComboBox pour l'ECUE
    ecueLabel = new QLabel("ECUE:", bandeauWidget);
    ecueComboBox = new QComboBox(bandeauWidget);
    bandeauLayout->addWidget(ecueLabel);
    bandeauLayout->addWidget(ecueComboBox);

    // Label et ComboBox pour le type de cours
    typeCoursLabel = new QLabel("Type de cours:", bandeauWidget);
    typeCoursComboBox = new QComboBox(bandeauWidget);
    bandeauLayout->addWidget(typeCoursLabel);
    bandeauLayout->addWidget(typeCoursComboBox);

    // Bouton Valider
    validerButton = new QPushButton("Valider", bandeauWidget);
    bandeauLayout->addWidget(validerButton);

    // Ajout du bandeau au layout principal
    mainLayout->addWidget(bandeauWidget);
    // ---------------- Fin Bandeau du Haut ----------------

    // Appel de la fonction pour initialiser les ComboBox ECUE et Type de Cours
    lectureCsvEcue(ecueComboBox, typeCoursComboBox);

    // ---------------- Bandeau du Bas --------------------
    infoWidget = new QWidget(centralWidget);
    infoWidget->hide();
    infoLayout = new QHBoxLayout(infoWidget);

    groupeValueLabel = new QLabel("");
    enseignantValueLabel = new QLabel("");
    ecueInfoValueLabel = new QLabel("");
    typeCoursInfoValueLabel = new QLabel("");

    groupeValueLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    enseignantValueLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ecueInfoValueLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    typeCoursInfoValueLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    infoLayout->addWidget(groupeValueLabel);
    infoLayout->addSpacing(20);
    infoLayout->addWidget(enseignantValueLabel);
    infoLayout->addSpacing(20);
    infoLayout->addWidget(ecueInfoValueLabel);
    infoLayout->addSpacing(20);
    infoLayout->addWidget(typeCoursInfoValueLabel);
    infoLayout->addStretch();

    mainLayout->addWidget(infoWidget);
    // ---------------- Fin Bandeau du Bas --------------------

    // ---------------- Grille de boutons --------------------
    gridLayout = new QGridLayout();

    // Jours de la semaine
    QStringList days = {"Mon", "Tue", "Wed", "Thu", "Fri"};
    for (int col = 0; col < 5; ++col) {
        dayLabel = new QLabel(days[col]);
        dayLabel->setAlignment(Qt::AlignCenter);
        dayLabel->setStyleSheet("font-weight: bold;");
        gridLayout->addWidget(dayLabel, 0, col + 1);
    }

    // Horaires
    for (int row = 0; row < 10; ++row) {
        hourLabel = new QLabel(QString("%1-%2h").arg(row + 8).arg(row + 9));
        hourLabel->setAlignment(Qt::AlignCenter);
        gridLayout->addWidget(hourLabel, row + 1, 0);
    }

    // Boutons
    for (int row = 0; row < 10; ++row) {
        if (row != 4){
            for (int col = 0; col < 5; ++col) {
                QPushButton *button = new QPushButton();
                // Connecter le signal clicked() du bouton à un slot (à définir plus tard)
                QObject::connect(button, &QPushButton::clicked, [=]() {
                    // Récupérer les informations associées au bouton (à implémenter plus tard)
                    afficherInfosBouton(ecueComboBox->currentText(), semaineSpinBox->value(), row, col);
                });
                gridLayout->addWidget(button, row + 1, col + 1);
            }
        }
    }

    // Widget pour la grille (pour la cacher/afficher facilement)
    gridWidget = new QWidget();
    gridWidget->setLayout(gridLayout);
    gridWidget->hide(); // Cacher la grille au démarrage
    mainLayout->addWidget(gridWidget); // Ajouter le widget au layout principal

    // Ajustements
    gridLayout->setSpacing(0);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // ----------- Connexion du bouton Valider ----------------
    QObject::connect(validerButton, SIGNAL(clicked()), this, SLOT(validerEtAfficher()));
}

void popupEdt::validerEtAfficher( )
{
    // Parcourir la grille de boutons
    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (row != 4){
                QPushButton *button = qobject_cast<QPushButton*>(gridLayout->itemAtPosition(row + 1, col + 1)->widget());
                if (button) {
                    button->setStyleSheet("");
                    button->setText("");
                    button->setEnabled(true);
                }
            }
        }
    }

    // Mettre à jour les labels du bandeau du bas
    mettreAJourBandeauBas(groupeValueLabel, enseignantValueLabel, ecueInfoValueLabel, typeCoursInfoValueLabel, ecueComboBox->currentText(), typeCoursComboBox->currentText());

    // Afficher le bandeau du bas
    infoWidget->show();

    // Afficher la grille
    gridWidget->show();
}

// Fonction pour lire le CSV et mettre à jour les ComboBox ECUE et Type de Cours
void popupEdt::lectureCsvEcue(QComboBox *ecueComboBox, QComboBox *typeCoursComboBox) {
    QString filePath = QDir::currentPath() + "/../../CSV/" + "Ecue.csv";
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier CSV" << filePath;
        return;
    }

    QTextStream in(&file);

    // Vider les ComboBox existants
    ecueComboBox->clear();
    typeCoursComboBox->clear();

    // Ignorer la première ligne (en-têtes)
    in.readLine();

    // Map pour stocker les types de cours par ECUE
    QMap<QString, QStringList> ecueTypesCoursMap;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        if (fields.size() >= 5) {
            QString nomECUE = fields[0];
            QString groupe = fields[3];
            QString typesCours = fields[4];

            QString ecueLabel = QString("%1 - %2").arg(groupe, nomECUE);

            // Stocker les types de cours pour cette ECUE
            QStringList types = typesCours.split("/");
            ecueTypesCoursMap[ecueLabel] = types;

            // Ajouter l'ECUE au ComboBox s'il n'y est pas déjà
            if (ecueComboBox->findText(ecueLabel) == -1) {
                ecueComboBox->addItem(ecueLabel);
            }
        }
    }

    file.close();

    // Connecter le signal currentTextChanged du ComboBox ECUE pour mettre à jour le ComboBox Type de Cours
    QObject::connect(ecueComboBox, &QComboBox::currentTextChanged, [=](const QString &ecue) {
        typeCoursComboBox->clear();
        if (ecueTypesCoursMap.contains(ecue)) {
            typeCoursComboBox->addItems(ecueTypesCoursMap[ecue]);
        }
    });

    // Sélectionner le premier élément et déclencher manuellement le signal pour mettre à jour le ComboBox Type de Cours au démarrage
    if (ecueComboBox->count() > 0) {
        ecueComboBox->setCurrentIndex(0); // Sélectionner le premier élément
        emit ecueComboBox->currentTextChanged(ecueComboBox->currentText()); // Déclencher le signal manuellement
    }
}

// Fonction pour mettre à jour les informations du bandeau du bas
void popupEdt::mettreAJourBandeauBas(QLabel *groupeValueLabel, QLabel *enseignantValueLabel, QLabel *ecueInfoValueLabel, QLabel *typeCoursInfoValueLabel, const QString &ecueLabel, const QString &typeCours) {
    QString filePath = QDir::currentPath() + "/../../CSV/" + "Ecue.csv"; // Assurez-vous que le chemin est correct
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier CSV" << filePath;
        return;
    }

    QTextStream in(&file);
    in.readLine(); // Ignorer la première ligne

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        if (fields.size() >= 5) {
            QString nomECUE = fields[0];
            QString nomEnseignant = fields[1];
            QString prenomEnseignant = fields[2];
            QString groupe = fields[3];
            QString typesCours = fields[4];

            // Vérifier si la ligne correspond à l'ECUE et au type de cours sélectionnés
            if (QString("%1 - %2").arg(groupe, nomECUE) == ecueLabel && typesCours.contains(typeCours)) {
                // Mettre à jour les labels du bandeau du bas
                groupeValueLabel->setText(QString("Groupe: %1").arg(groupe));
                enseignantValueLabel->setText(QString("Enseignant: %1 %2").arg(nomEnseignant.toUpper(), prenomEnseignant));
                enseignantValueLabel->setStyleSheet("QLabel { color : blue;font-weight: bold;}");
                ecueInfoValueLabel->setText(QString("ECUE: %1").arg(nomECUE));
                typeCoursInfoValueLabel->setText(QString("Type de cours: %1").arg(typeCours));
                // Bloquer les boutons indisponibles
                bloquerBoutonsIndisponibles(semaineSpinBox->value(), nomEnseignant, groupe);
                break; // On a trouvé la ligne correspondante, pas besoin de continuer
            }
        }
    }

    file.close();
}

void popupEdt::afficherInfosBouton(const QString &ecueLabel, int semaine, int row, int col) {
    // Extraire le nom de l'ECUE et le groupe à partir de ecueLabel
    QString groupe = ecueLabel.split(" - ").at(0);
    QString nomECUE = ecueLabel.split(" - ").at(1);

    // Récupérer le nom et le prénom de l'enseignant à partir du CSV
    QString nomEnseignant, prenomEnseignant;
    QString filePath = QDir::currentPath() + "/../../CSV/" + "Ecue.csv"; // Assurez-vous que le chemin est correct
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        in.readLine(); // Ignorer la première ligne
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            if (fields.size() >= 3 && fields[0] == nomECUE && fields[3] == groupe) {
                nomEnseignant = fields[1];
                prenomEnseignant = fields[2];
                break;
            }
        }
        file.close();
    }

    // Déterminer le jour et l'heure de début à partir de row et col
    days = {"Mon", "Tue", "Wed", "Thu", "Fri"};
    QString jour = days[col];
    int heureDebut = row + 8; // +8 car les horaires commencent à 8h

    // Afficher les informations dans la console
    qDebug() << "ECUE:" << nomECUE;
    qDebug() << "Enseignant:" << nomEnseignant << prenomEnseignant;
    qDebug() << "Groupe:" << groupe;
    qDebug() << "Semaine:" << semaine;
    qDebug() << "Date de début:" << QString("%1 %2h").arg(jour).arg(heureDebut);
    qDebug() << "--------------------";
}

// Fonction pour bloquer les boutons des créneaux où aucune salle n'est disponible
void popupEdt::bloquerBoutonsIndisponibles(int semaine, const QString& enseignant, const QString& groupe) {
    // Jours de la semaine
    days = {"Mon", "Tue", "Wed", "Thu", "Fri"};

    // Heures de début et de fin
    QTime startTime(8, 0);
    QTime endTime(18, 0);

    // Récupérer le type de cours sélectionné
    QString typeCours = typeCoursComboBox->currentText();

    // Liste de toutes les salles
    QList<int> roomNumbers = readRoomNumbersFromCSV(typeCours);

    // Parcourir la grille de boutons
    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (row != 4){
                // Calculer l'heure de début et de fin pour ce bouton
                QTime heureDebut(row + 8, 0);
                QTime heureFin = heureDebut.addSecs(3600);

                // Construire le créneau horaire
                QString jour = days[col];
                QString debut = QString("%1 %2").arg(jour).arg(heureDebut.toString("HH:mm"));
                QString fin = QString("%1 %2").arg(jour).arg(heureFin.toString("HH:mm"));

                // Vérifier la disponibilité des salles pour ce créneau
                bool salleDisponible = false;
                for (int roomNumber : roomNumbers) {
                    if (isRoomAvailable(roomNumber, semaine, debut, fin)) {
                        salleDisponible = true;
                        break;
                    }
                }

                // Désactiver le bouton si aucune salle n'est disponible
                QPushButton *button = qobject_cast<QPushButton*>(gridLayout->itemAtPosition(row + 1, col + 1)->widget());
                if (button && !salleDisponible) {
                    button->setStyleSheet("QPushButton {color: red;}");
                    button->setText("No room available");
                    button->setEnabled(false);
                }

                // Vérifier si l'enseignant est disponible pour ce créneau
                if (button && !isTeacherAvailable(enseignant, semaine, debut, fin)) {
                    button->setStyleSheet("background-color: blue");
                    button->setEnabled(false);
                }

                // Vérifier si le groupe est disponible pour ce créneau
                if (button && !isGroupAvailable(groupe, semaine, debut, fin)) {
                    button->setStyleSheet("background-color: green");
                    button->setEnabled(false);
                }

            }
        }
    }
}


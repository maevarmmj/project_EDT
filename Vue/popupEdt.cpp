#include "popupEdt.h"

popupEdt::popupEdt(QWidget *parent) : QMainWindow(parent) {
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowModality(Qt::ApplicationModal);
    QString file(QDir::currentPath() + "/../../Ressources/planning.ico");
    QIcon icon(file);
    setWindowIcon(icon);
    // Initialize the database
    initDatabase(db);

    // Fenêtre principale
    this->setWindowTitle("Mise à jour edt");

    // Widget central
    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    // Layout principal
    mainLayout = new QVBoxLayout(centralWidget);

    // ---------------- Bandeau du Haut --------------------
    bandeauWidget = new QWidget(centralWidget);
    bandeauLayout = new QHBoxLayout(bandeauWidget);

    // Label et SpinBox pour la semaine
    semaineLabel = new QLabel("Semaine :", bandeauWidget);
    semaineSpinBox = new QSpinBox(bandeauWidget);
    semaineSpinBox->setRange(1, 52);
    bandeauLayout->addWidget(semaineLabel);
    bandeauLayout->addWidget(semaineSpinBox);

    // Label et ComboBox pour l'ECUE
    ecueLabel = new QLabel("ECUE :", bandeauWidget);
    ecueComboBox = new QComboBox(bandeauWidget);
    bandeauLayout->addWidget(ecueLabel);
    bandeauLayout->addWidget(ecueComboBox);

    // Label et ComboBox pour le type de cours
    typeCoursLabel = new QLabel("Type de cours :", bandeauWidget);
    typeCoursComboBox = new QComboBox(bandeauWidget);
    bandeauLayout->addWidget(typeCoursLabel);
    bandeauLayout->addWidget(typeCoursComboBox);

    // Bouton Valider
    validerButton = new QPushButton("Valider", bandeauWidget);
    bandeauLayout->addWidget(validerButton);

    bandeauWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
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

    infoWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    mainLayout->addWidget(infoWidget);
    // ---------------- Fin Bandeau du Bas --------------------

    // ---------------- Grille de boutons --------------------
    gridLayout = new QGridLayout();

    QStringList jours = {"Lun", "Mar", "Mer", "Jeu", "Ven"};
    for (int col = 0; col < 5; ++col) {
        dayLabel = new QLabel(jours[col]);
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
                button->setCheckable(true);
                // Connecter le signal clicked() du bouton à un slot (à définir plus tard)
                connect(button, &QPushButton::clicked, this, &popupEdt::onButtonClicked);
                gridLayout->addWidget(button, row + 1, col + 1);
            }
        }
    }


    // Widget pour la grille (pour la cacher/afficher facilement)
    gridWidget = new QWidget();
    gridWidget->setLayout(gridLayout);
    gridWidget->hide(); // Cacher la grille au démarrage
    gridWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    mainLayout->addWidget(gridWidget); // Ajouter le widget au layout principal

    // Boutons Valider et Annuler
    annulerButtonGrid = new QPushButton("Annuler", this);
    validerButtonGrid = new QPushButton("Valider", this);

    // Layout pour les boutons Valider et Annuler
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(annulerButtonGrid);
    buttonsLayout->addWidget(validerButtonGrid);
    mainLayout->addLayout(buttonsLayout);

    // Connecter les signaux des boutons Valider et Annuler
    connect(validerButtonGrid, &QPushButton::clicked, this, &popupEdt::validerSelection);
    connect(annulerButtonGrid, &QPushButton::clicked, this, &popupEdt::annulerSelection);

    validerButtonGrid->hide();
    annulerButtonGrid->hide();

    // Ajustements
    gridLayout->setSpacing(0);
    mainLayout->setSpacing(10);
    mainLayout->addStretch();
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // ----------- Connexion du bouton Valider ----------------
    QObject::connect(validerButton, SIGNAL(clicked()), this, SLOT(validerEtAfficher()));
}

popupEdt::~popupEdt(){
    emit windowClosed();
}

void popupEdt::validerEtAfficher( )
{
    // Parcourir la grille de boutons
    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (row != 4){
                QPushButton *button = qobject_cast<QPushButton*>(gridLayout->itemAtPosition(row + 1, col + 1)->widget());
                if (button) {
                    button->setStyleSheet(""); // Réinitialiser le style
                    button->setText(""); // Effacer le texte
                    button->setEnabled(true); // Réactiver le bouton
                    button->setCheckable(true);
                    button->setChecked(false);
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
    QString filePath = QDir::currentPath() + "/../../CSV/" + "Ecue.csv";
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

        if (fields.size() >= 7) {
            QString nomECUE = fields[0];
            QString nomEnseignant = fields[1];
            QString prenomEnseignant = fields[2];
            QString groupe = fields[3];
            QString typesCours = fields[4];
            QString heuresAPlacer = fields[6];

            // Vérifier si la ligne correspond à l'ECUE et au type de cours sélectionnés
            if (QString("%1 - %2").arg(groupe, nomECUE) == ecueLabel) {
                // Mettre à jour les labels du bandeau du bas
                groupeValueLabel->setText(QString("Groupe: %1").arg(groupe));
                groupeValueLabel->setStyleSheet("QLabel { color : green;font-weight: bold;}");
                enseignantValueLabel->setText(QString("Enseignant: %1 %2").arg(nomEnseignant.toUpper(), prenomEnseignant));
                enseignantValueLabel->setStyleSheet("QLabel { color : blue;font-weight: bold;}");
                ecueInfoValueLabel->setText(QString("ECUE: %1").arg(nomECUE));

                // Récupérer l'index du type de cours sélectionné
                QStringList typesCoursList = typesCours.split("/");
                int typeCoursIndex = typesCoursList.indexOf(typeCours);

                // Récupérer les heures à placer correspondantes
                if (typeCoursIndex != -1) {
                    QStringList heuresAPlacerList = heuresAPlacer.split("/");
                    if (typeCoursIndex < heuresAPlacerList.size()) {
                        heuresRestantes = heuresAPlacerList[typeCoursIndex];
                        typeCoursInfoValueLabel->setText(QString("Heures à placer: %1").arg(heuresRestantes));
                    } else {
                        typeCoursInfoValueLabel->setText("Heures à placer : N/A");
                    }
                } else {
                    typeCoursInfoValueLabel->setText("Heures à placer : N/A");
                }

                // Bloquer les boutons indisponibles
                bloquerBoutonsIndisponibles(semaineSpinBox->value(), nomEnseignant, groupe);
                break;
            }
        }
    }

    file.close();
}

// Fonction pour bloquer les boutons des créneaux où aucune salle n'est disponible
void popupEdt::bloquerBoutonsIndisponibles(int semaine, const QString& enseignant, const QString& groupe) {
    // Heures de début et de fin
    QTime startTime(8, 0);
    QTime endTime(18, 0);

    // Récupérer le type de cours sélectionné
    QString typeCours = typeCoursComboBox->currentText();

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

                // Liste de toutes les salles compatibles avec le type de cours
                QList<int> roomNumbers = readRoomNumbersFromCSV(typeCours);

                // Filtrer les salles disponibles
                QList<int> availableRooms;
                for (int roomNumber : roomNumbers) {
                    if (isRoomAvailable(roomNumber, semaine, debut, fin)) {
                        availableRooms.append(roomNumber);
                    }
                }
                minButtonHeight = 40;
                QPushButton *button = qobject_cast<QPushButton*>(gridLayout->itemAtPosition(row + 1, col + 1)->widget());
                if (button) {
                    // Réinitialiser le style et l'état du bouton
                    button->setStyleSheet("");
                    button->setText("");
                    button->setEnabled(true);
                    button->setToolTip("");
                    button->setMinimumHeight(minButtonHeight);

                    // Mettre à jour le texte du bouton avec les salles disponibles
                    if (!availableRooms.isEmpty()) {
                        QStringList roomLabels;
                        for (int room : availableRooms) {
                            roomLabels << QString::number(room);
                        }

                        // Limiter le nombre de caractères affichés sur le bouton
                        QString roomsText = roomLabels.join(", ");
                        const int maxChars = 10;
                        if (roomsText.length() > maxChars) {
                            roomsText = roomsText.left(maxChars) + "...";
                        }

                        button->setText(roomsText);
                        button->setToolTip(QString("Salles disponibles : %1").arg(roomLabels.join(", ")));
                    } else {
                        button->setStyleSheet("QPushButton {color: red;}");
                        button->setText("Aucune salle\ndisponible");
                        button->setEnabled(false);
                        button->setToolTip("Aucune salle disponible");
                    }

                    // Vérifier si l'enseignant est disponible pour ce créneau
                    if (!isTeacherAvailable(enseignant, semaine, debut, fin)) {
                        button->setStyleSheet("background-color: blue; color: white");
                        button->setText("Enseignant\nIndisponible");
                        button->setEnabled(false);
                        button->setToolTip("");
                    }

                    // Vérifier si le groupe est disponible pour ce créneau
                    if (!isGroupAvailable(groupe, semaine, debut, fin)) {
                        button->setStyleSheet("background-color: green; color: white");
                        button->setEnabled(false);
                        button->setText(QString("%1\nIndisponible").arg(groupe));
                        button->setToolTip("");
                    }
                }
            }
        }
    }
}

void popupEdt::onButtonClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (!clickedButton) return;
    if (selectedButtons.size() >= heuresRestantes.toInt()){
        clickedButton->setChecked(false);
        qDebug() << "Toute les heures ont été selectionné pour ce module";
        return;
    }

    // Retrieve the row and column of the clicked button
    int row = -1, col = -1;
    for (int r = 0; r < gridLayout->rowCount(); ++r) {
        for (int c = 0; c < gridLayout->columnCount(); ++c) {
            if (gridLayout->itemAtPosition(r, c) && gridLayout->itemAtPosition(r, c)->widget() == clickedButton) {
                row = r - 1;
                col = c - 1;
                break;
            }
        }
        if (row != -1) break;
    }

    // Calculer l'heure de début et de fin pour ce bouton
    QTime heureDebut(row + 8, 0);
    QTime heureFin = heureDebut.addSecs(3600);

    // Construire le créneau horaire
    QString jour = days[col];
    QString debut = QString("%1 %2").arg(jour).arg(heureDebut.toString("HH:mm"));
    QString fin = QString("%1 %2").arg(jour).arg(heureFin.toString("HH:mm"));

    // Récupérer le type de cours sélectionné
    QString typeCours = typeCoursComboBox->currentText();

    // Liste de toutes les salles
    QList<int> roomNumbers = readRoomNumbersFromCSV(typeCours);

    //filtrer les salles libres
    QList<int> availableRooms;
    for (int roomNumber : roomNumbers) {
        if (isRoomAvailable(roomNumber, semaineSpinBox->value(), debut, fin)) {
            availableRooms.append(roomNumber);
        }
    }

    if (clickedButton->isChecked()) {
        // Bouton sélectionné
        if (row != -1 && col != -1 && !availableRooms.isEmpty()) {
            // Créer un QComboBox pour la sélection de la salle
            QComboBox *roomComboBox = new QComboBox();
            roomComboBox->addItem("......");
            for (int room : availableRooms) {
                roomComboBox->addItem(QString::number(room));
            }
            roomComboBox->setMinimumHeight(minButtonHeight);

            // Remplacer le bouton par le QComboBox dans le layout
            gridLayout->replaceWidget(clickedButton, roomComboBox);
            clickedButton->hide(); // Cacher le bouton original

            // Connecter le signal currentIndexChanged du QComboBox à un slot pour gérer la sélection de la salle
            connect(roomComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
                // La salle a été sélectionnée
                int selectedRoom = roomComboBox->itemText(index).toInt();

                // Stocker les informations du bouton sélectionné
                QVariantMap buttonInfo;
                buttonInfo["row"] = row;
                buttonInfo["col"] = col;
                buttonInfo["ecue"] = ecueComboBox->currentText();
                buttonInfo["semaine"] = semaineSpinBox->value();
                buttonInfo["salle"] = selectedRoom;
                buttonInfo["debut"] = debut;
                buttonInfo["fin"] = fin;
                selectedButtonInfos.append(buttonInfo);

                // Créer un nouveau bouton pour remplacer le QComboBox
                QPushButton *newButton = new QPushButton(QString("Salle : %1").arg(selectedRoom));
                connect(newButton, &QPushButton::clicked, this, &popupEdt::onButtonClicked);
                newButton->setMinimumHeight(minButtonHeight);
                newButton->setCheckable(true);
                newButton->setChecked(true);
                newButton->setStyleSheet("background-color: gray; color: white");

                // Remplacer le QComboBox par le nouveau bouton
                gridLayout->replaceWidget(roomComboBox, newButton);
                roomComboBox->deleteLater(); // Supprimer le QComboBox

                // Mettre à jour la liste des boutons sélectionnés
                selectedButtons.removeAll(clickedButton); // Supprimer l'ancien bouton
                selectedButtons.append(newButton); // Ajouter le nouveau bouton

                // Mettre à jour l'apparence du bouton
                newButton->update();

                // Afficher les boutons de validation et d'annulation
                validerButtonGrid->show();
                annulerButtonGrid->show();
            });
        } else if (availableRooms.isEmpty()) {
            // Aucune salle disponible
            clickedButton->setChecked(false); // Désélectionner le bouton
            qDebug() << "Aucune salle disponible pour ce créneau.";
        }
    } else {
        // Bouton désélectionné
        if (row != -1 && col != -1) {
            // Trouver et supprimer les informations du bouton désélectionné
            for (int i = 0; i < selectedButtonInfos.size(); ++i) {
                if (selectedButtonInfos[i]["row"] == row && selectedButtonInfos[i]["col"] == col) {
                    selectedButtonInfos.removeAt(i);
                    break;
                }
            }

            // Désélectionner le bouton dans la liste (si trouvé)
            QPushButton *buttonToRemove = nullptr;
            for (QPushButton *btn : selectedButtons) {
                if (gridLayout->itemAt(gridLayout->indexOf(btn))->widget() == clickedButton) {
                    buttonToRemove = btn;
                    break;
                }
            }
            if (buttonToRemove) {
                selectedButtons.removeOne(buttonToRemove);
            }

            QStringList roomLabels;
            for (int room : availableRooms) {
                roomLabels << QString::number(room);
            }

            // Réinitialiser l'apparence du bouton
            clickedButton->setStyleSheet("");
            // Limiter le nombre de caractères affichés sur le bouton
            QString roomsText = roomLabels.join(", ");
            const int maxChars = 10;
            if (roomsText.length() > maxChars) {
                roomsText = roomsText.left(maxChars) + "...";
            }
            clickedButton->setText(roomsText);
            clickedButton->setCheckable(true);
            clickedButton->setChecked(false);
            clickedButton->show();
        }

        // Cacher les boutons de validation et d'annulation si aucun bouton n'est sélectionné
        if (selectedButtons.isEmpty()) {
            validerButtonGrid->hide();
            annulerButtonGrid->hide();
        }
    }
}

void popupEdt::onRoomSelected(int roomNumber)
{
    // Gérer la sélection de la salle ici
    qDebug() << "Salle sélectionnée :" << roomNumber;
    // Vous pouvez ajouter le numéro de la salle à selectedButtonInfos ou effectuer d'autres actions nécessaires
}

void popupEdt::validerSelection() {
    // Afficher les informations des boutons sélectionnés et insérer dans la base de données
    for (const QVariantMap &buttonInfo : selectedButtonInfos) {
        QString ecueLabel = buttonInfo["ecue"].toString();
        int semaine = buttonInfo["semaine"].toInt();
        int numeroSalle = buttonInfo["salle"].toInt();
        QString debut = buttonInfo["debut"].toString();
        QString fin = buttonInfo["fin"].toString();    // Récupérer le type de cours sélectionné
        QString typeCours = typeCoursComboBox->currentText();

        // Extraire le nom de l'ECUE et le groupe à partir de ecueLabel
        QString groupe = ecueLabel.split(" - ").at(0);
        QString nomECUE = ecueLabel.split(" - ").at(1);

        // Récupérer le nom et le prénom de l'enseignant à partir du CSV
        QString nomEnseignant, prenomEnseignant, typesCours, HeuresCours, HeuresAPlacer;
        QString filePath = QDir::currentPath() + "/../../CSV/" + "Ecue.csv";
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            in.readLine();
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList fields = line.split(",");
                if (fields.size() >= 3 && fields[0] == nomECUE && fields[3] == groupe) {
                    nomEnseignant = fields[1];
                    prenomEnseignant = fields[2];
                    typesCours = fields[4];
                    HeuresCours = fields[5];
                    HeuresAPlacer = fields[6];
                    EcueControleur temps = EcueControleur(nomECUE, nomEnseignant, prenomEnseignant, groupe, typesCours, HeuresCours, HeuresAPlacer);
                    temps.decrementerHeuresCours(StrToCours(typeCours.toStdString()), 1);
                    break;
                }
            }
            file.close();
        }

        // Insérer la réservation dans la base de données
        if (insertReservation(numeroSalle, nomECUE, nomEnseignant, prenomEnseignant, groupe, semaine, debut, fin)) {
            qDebug() << "Réservation ajoutée avec succès. Salle:" << numeroSalle << "ECUE:" << nomECUE << "Enseignant:" << nomEnseignant << prenomEnseignant << "Groupe:" << groupe << "Type de cours:" << typeCours << "Semaine:" << semaine << "Début:" << debut << "Fin:" << fin;
        } else {
            qDebug() << "Erreur lors de l'ajout de la réservation.";
        }
        validerEtAfficher( );
    }

    // Réinitialiser la sélection
    resetSelection();

    // Cacher les boutons de validation et d'annulation
    validerButtonGrid->hide();
    annulerButtonGrid->hide();

    emit windowClosed();
}

void popupEdt::annulerSelection() {
    // Réinitialiser la sélection
    resetSelection();

    // Cacher les boutons de validation et d'annulation
    validerButtonGrid->hide();
    annulerButtonGrid->hide();
}

void popupEdt::resetSelection() {
    // Désélectionner tous les boutons sélectionnés
    for (QPushButton *button : selectedButtons) {
        button->setChecked(false);
    }
    validerEtAfficher();
    selectedButtons.clear();
    selectedButtonInfos.clear();
}


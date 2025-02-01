#include "edteseoWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    setupActions();
    loadGroups(TRUE);
    QSqlDatabase db;

    // ------ Initialisation DB --------
    initDatabase(db);
    QString file(QDir::currentPath() + "/../../Ressources/planning.ico");
    QIcon icon(file);
    setWindowIcon(icon);
    this->setFixedSize(880, 400);
    this->setWindowTitle("Emploi du temps");
}

void MainWindow::setupUI() {
    centralWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout *topBarLayout = new QHBoxLayout();

    QLabel *groupLabel = new QLabel("Personnel :", this);
    topBarLayout->addWidget(groupLabel);

    // ------ Menu déroulant groupes --------
    groupComboBox = new QComboBox(this);
    topBarLayout->addWidget(groupComboBox);

    topBarLayout->addStretch();

    // Bouton "-"
    remButton = new QPushButton("", this);
    remButton->setIcon(QIcon("../../Ressources/moins.png"));
    remButton->setStyleSheet("padding: 5px;");
    topBarLayout->addWidget(remButton);

    remGroupButton = new QPushButton("Groupe", this);
    remEnseignantButton = new QPushButton("Enseignant", this);
    remSalleButton = new QPushButton("Salle", this);
    remECUEButton = new QPushButton("ECUE", this);
    remUEButton = new QPushButton("UE", this);

    remGroupButton->setVisible(false);
    remEnseignantButton->setVisible(false);
    remSalleButton->setVisible(false);
    remECUEButton->setVisible(false);
    remUEButton->setVisible(false);

    topBarLayout->addWidget(remGroupButton);
    topBarLayout->addWidget(remEnseignantButton);
    topBarLayout->addWidget(remSalleButton);
    topBarLayout->addWidget(remECUEButton);
    topBarLayout->addWidget(remUEButton);


    // Bouton "+"
    addButton = new QPushButton("", this);
    addButton->setIcon(QIcon("../../Ressources/plus.png"));
    addButton->setStyleSheet("padding: 5px;");
    topBarLayout->addWidget(addButton);

    addGroupButton = new QPushButton("Élement", this);
    addECUEButton = new QPushButton("ECUE", this);
    addUEButton = new QPushButton("UE", this);

    addGroupButton->setVisible(false);
    addECUEButton->setVisible(false);
    addUEButton->setVisible(false);

    topBarLayout->addWidget(addGroupButton);
    topBarLayout->addWidget(addECUEButton);
    topBarLayout->addWidget(addUEButton);


    mainLayout->addLayout(topBarLayout);

    updateButton = new QPushButton("Mettre à jour l'emploi du temps", this);

    QHBoxLayout *updateLayout = new QHBoxLayout();
    updateLayout->addWidget(updateButton, 0, Qt::AlignHCenter);

    mainLayout->addLayout(updateLayout);


    // ------ Tableau --------
    setupTable();
    mainLayout->addWidget(table);

    setCentralWidget(centralWidget);
}

// ------ Configuration de la table --------
void MainWindow::setupTable() {
    table = new QTableWidget(9, 8, this);
    table->setStyleSheet("background-color: #f9f5fa;"
                         "border-radius: 15px; ");
    table->setHorizontalHeaderLabels({
        "Matière", "Enseignant", "H. totales", "H. CM",
        "H. TD", "H. Elec", "H. Info", "H. Exam"
    });
    table->setEditTriggers(QAbstractItemView::NoEditTriggers); // Interdire l'édition
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed); // Fixe juste les lignes

    table->setColumnWidth(0, 120); // Matière
    table->setColumnWidth(1, 120); // Enseignant
    table->setColumnWidth(2, 100); // Heures totales
    table->setColumnWidth(3, 100); // Heures CM
    table->setColumnWidth(4, 100); // Heures TD
    table->setColumnWidth(5, 100); // Heures Elec
    table->setColumnWidth(6, 100); // Heures Info
    table->setColumnWidth(7, 100); // Heures Exam
}

// ------ Connexion de tous les boutons avec leurs actions --------

void MainWindow::setupActions() {
    connect(groupComboBox, &QComboBox::currentTextChanged, this, &MainWindow::onComboBoxSelectionChanged);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::toggleButtonsVisibility);
    connect(addGroupButton, &QPushButton::clicked, this, &MainWindow::addGroup);
    connect(addECUEButton, &QPushButton::clicked, this, &MainWindow::addECUE);
    connect(addUEButton, &QPushButton::clicked, this, &MainWindow::addUE);

    connect(remButton, &QPushButton::clicked, this, &MainWindow::toggleRemButtonsVisibility);
    connect(remGroupButton, &QPushButton::clicked, this, &MainWindow::remGroup);
    connect(remEnseignantButton, &QPushButton::clicked, this, &MainWindow::remEnseignant);
    connect(remSalleButton, &QPushButton::clicked, this, &MainWindow::remSalle);
    connect(remECUEButton, &QPushButton::clicked, this, &MainWindow::remECUE);
    connect(remUEButton, &QPushButton::clicked, this, &MainWindow::remUE);

    connect(updateButton, &QPushButton::clicked, this, &MainWindow::updateEdt);
}

// ------ MAJ de toutes les informations lorsque la comboBox du "Personnel" change --------

void MainWindow::onComboBoxSelectionChanged(const QString &selectedText) {
    for (int i = 0; i < table->rowCount(); ++i) {
        for (int j = 0; j < table->columnCount(); ++j) {
            table->setItem(i, j, new QTableWidgetItem("")); // Effacer les données des cellules
        }
    }

    QFile file(QDir::currentPath() + "/../../CSV/" + "Ecue.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    if (!in.atEnd()) {
        in.readLine();
    }

    int row = 0;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty()) {
            QStringList columns = line.split(",");

            if (columns.size() >= 7) {
                QString ecueName = columns[0];
                QString enseignant = columns[1] + " " + columns[2];
                QString group = columns[3];
                QStringList typesCours = columns[4].split("/");
                QStringList heuresCours = columns[5].split("/");
                QStringList heuresRestantes = columns[6].split("/");

                // ------ En-tête du tableau (change selon si c'est un groupe ou un enseignant) --------
                if (group == selectedText || enseignant == selectedText) {
                    table->setHorizontalHeaderLabels({
                        "Matière", selectedText == group ? "Enseignant" : "Groupe étudiants", "H. totales", "H. CM",
                        "H. TD", "H. Elec", "H. Info", "H. Exam"
                    });

                    table->setItem(row, 0, new QTableWidgetItem(ecueName));
                    table->item(row, 0)->setTextAlignment(Qt::AlignCenter);
                    table->setItem(row, 1, new QTableWidgetItem(selectedText == group ? enseignant : group));
                    table->item(row, 1)->setTextAlignment(Qt::AlignCenter);

                    int totalHeures = 0;
                    int totalRestantes = 0;
                    bool typeFound[5] = {false, false, false, false, false}; // CM, TD, TP_ELEC, TP_INFO, EXAM

                    // ------ Ajouter les heures par type de cours (totales et à placer) --------
                    for (int i = 0; i < typesCours.size(); ++i) {
                        QString type = typesCours[i];
                        int heures = heuresCours[i].toInt();
                        int restantes = heuresRestantes[i].toInt();

                        totalHeures += heures;
                        totalRestantes += restantes;

                        if (type == "CM") {
                            table->setItem(row, 3, new QTableWidgetItem(QString("%1 (A placer : %2)").arg(heures).arg(restantes)));
                            table->item(row, 3)->setTextAlignment(Qt::AlignCenter);

                            typeFound[0] = true;
                        } else if (type == "TD") {
                            table->setItem(row, 4, new QTableWidgetItem(QString("%1 (A placer : %2)").arg(heures).arg(restantes)));
                            table->item(row, 4)->setTextAlignment(Qt::AlignCenter);

                            typeFound[1] = true;
                        } else if (type == "TP_ELEC") {
                            table->setItem(row, 5, new QTableWidgetItem(QString("%1 (A placer : %2)").arg(heures).arg(restantes)));
                            table->item(row, 5)->setTextAlignment(Qt::AlignCenter);

                            typeFound[2] = true;
                        } else if (type == "TP_INFO") {
                            table->setItem(row, 6, new QTableWidgetItem(QString("%1 (A placer : %2)").arg(heures).arg(restantes)));
                            table->item(row, 6)->setTextAlignment(Qt::AlignCenter);

                            typeFound[3] = true;
                        } else if (type == "EXAMEN") {
                            table->setItem(row, 7, new QTableWidgetItem(QString("%1 (A placer : %2)").arg(heures).arg(restantes)));
                            table->item(row, 7)->setTextAlignment(Qt::AlignCenter);

                            typeFound[4] = true;
                        }
                    }

                    table->setItem(row, 2, new QTableWidgetItem(QString("%1 (A placer : %2)").arg(totalHeures).arg(totalRestantes)));

                    // ------ Remplir les colonnes non remplies avec des 0 --------
                    if (!typeFound[0]) {
                        table->setItem(row, 3, new QTableWidgetItem("0"));
                        table->item(row, 3)->setTextAlignment(Qt::AlignCenter);}
                    if (!typeFound[1]) {
                        table->setItem(row, 4, new QTableWidgetItem("0"));
                        table->item(row, 4)->setTextAlignment(Qt::AlignCenter);
                    }
                    if (!typeFound[2]) {
                        table->setItem(row, 5, new QTableWidgetItem("0"));
                        table->item(row, 5)->setTextAlignment(Qt::AlignCenter);
                    }
                    if (!typeFound[3]) {
                        table->setItem(row, 6, new QTableWidgetItem("0"));
                        table->item(row, 6)->setTextAlignment(Qt::AlignCenter);
                    }
                    if (!typeFound[4]) {
                        table->setItem(row, 7, new QTableWidgetItem("0"));
                        table->item(row, 7)->setTextAlignment(Qt::AlignCenter);
                    }

                    row++;
                }
            }
        }
    }

    file.close();
}

// ------ Quand on appuie sur le "+", ça visibilise les autres boutons --------

void MainWindow::toggleButtonsVisibility() {
    bool isVisible = addGroupButton->isVisible();
    addGroupButton->setVisible(!isVisible);
    addECUEButton->setVisible(!isVisible);
    addUEButton->setVisible(!isVisible);
}

// ------ Quand on appuie sur le "-", ça visibilise les autres boutons --------

void MainWindow::toggleRemButtonsVisibility() {
    bool isVisible = remGroupButton->isVisible();
    remGroupButton->setVisible(!isVisible);
    remEnseignantButton->setVisible(!isVisible);
    remSalleButton->setVisible(!isVisible);
    remECUEButton->setVisible(!isVisible);
    remUEButton->setVisible(!isVisible);
}


// ------ Fenêtre "Ajouter Groupe étudiants" --------

void MainWindow::addGroup() {
    AjouterGroupeWindow *addgroup = new AjouterGroupeWindow();
    connect(addgroup, &AjouterGroupeWindow::windowClosed, this, &MainWindow::refreshMainWindow);
    addgroup->show();
}

// ------ Fenêtre "Ajouter ECUE" --------

void MainWindow::addECUE() {
    if (!checkEnseignantsGroupesFiles()) {
        QMessageBox::warning(this, "Erreur", "Veuillez créer un enseignant et des étudiants avant de créer une ECUE.");
        return;
    }
    AjoutEcueWindow *addecue = new AjoutEcueWindow();
    connect(addecue, &AjoutEcueWindow::windowClosed, this, &MainWindow::refreshMainWindow);
    addecue->show();

}

// ------ Fenêtre "Ajouter UE" (en cours) --------

void MainWindow::addUE() {
    if (!checkECUEFile()) {
        QMessageBox::warning(this, "Erreur", "Veuillez créer une ECUE avant de créer une UE.");
        return;
    }
    AjouterUEWindow *addUE = new AjouterUEWindow();
    addUE->show();
}

// ------ Fenêtre "Supprimer Groupe étudiants" --------

void MainWindow::remGroup() {
    QFile fileGroupes(QDir::currentPath() + "/../../CSV/Groupes.csv");
    if (!fileGroupes.exists()) {
        QMessageBox::warning(this, "Erreur", "Veuillez créer un groupe avant !");
        return;
    }
    if (!fileGroupes.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier CSV";
        return;
    }
    QTextStream in(&fileGroupes);
    // Ignorer la première ligne (en-têtes)
    in.readLine();
    if (in.atEnd()){
        QMessageBox::warning(this, "Erreur", "Aucune ECUE disponible !");
        return;
    }
    SupprimerGroupeWindow *remgroup = new SupprimerGroupeWindow();
    connect(remgroup, &SupprimerGroupeWindow::windowClosed, this, &MainWindow::refreshMainWindow);
    remgroup->show();
}

// ------ Fenêtre "Supprimer Enseignant" --------

void MainWindow::remEnseignant() {
    QFile fileEnseignants(QDir::currentPath() + "/../../CSV/Enseignants.csv");
    if (!fileEnseignants.exists()) {
        QMessageBox::warning(this, "Erreur", "Veuillez créer un enseignant avant !");
        return;
    }
    if (!fileEnseignants.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier CSV";
        return;
    }
    QTextStream in(&fileEnseignants);
    // Ignorer la première ligne (en-têtes)
    in.readLine();
    if (in.atEnd()){
        QMessageBox::warning(this, "Erreur", "Aucune ECUE disponible !");
        return;
    }
    SupprimerEnseignantWindow *remenseignant = new SupprimerEnseignantWindow();
    connect(remenseignant, &SupprimerEnseignantWindow::windowClosed, this, &MainWindow::refreshMainWindow);
    remenseignant->show();
}

// ------ Fenêtre "Supprimer Salle" --------

void MainWindow::remSalle() {
    QFile fileSalles(QDir::currentPath() + "/../../CSV/Salles.csv");
    if (!fileSalles.exists()) {
        QMessageBox::warning(this, "Erreur", "Veuillez créer une salle avant !");
        return;
    }
    if (!fileSalles.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier CSV";
        return;
    }
    QTextStream in(&fileSalles);
    // Ignorer la première ligne (en-têtes)
    in.readLine();
    if (in.atEnd()){
        QMessageBox::warning(this, "Erreur", "Aucune ECUE disponible !");
        return;
    }
    SupprimerSalleWindow *remsalle = new SupprimerSalleWindow();
    connect(remsalle, &SupprimerSalleWindow::salleWindowClosed, this, &MainWindow::refreshMainWindow);
    remsalle->show();}

// ------ Fenêtre "Supprimer ECUE" --------

void MainWindow::remECUE() {
    QFile fileEcue(QDir::currentPath() + "/../../CSV/Ecue.csv");
    if (!fileEcue.exists()) {
        QMessageBox::warning(this, "Erreur", "Veuillez créer une ECUE avant !");
        return;
    }
    if (!fileEcue.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier CSV";
        return;
    }
    QTextStream in(&fileEcue);
    // Ignorer la première ligne (en-têtes)
    in.readLine();
    if (in.atEnd()){
        QMessageBox::warning(this, "Erreur", "Aucune ECUE disponible !");
        return;
    }
    SupprimerEcueWindow *suppEcue = new SupprimerEcueWindow();
    connect(suppEcue, &SupprimerEcueWindow::ecueWindowClosed, this, &MainWindow::refreshMainWindow);
    suppEcue->show();
}

// ------ Fenêtre "Supprimer UE" (en cours) --------

void MainWindow::remUE() {
    QFile fileGroupes(QDir::currentPath() + "/../../CSV/UE.csv");
    if (!fileGroupes.exists()) {
        QMessageBox::warning(this, "Erreur", "Veuillez créer une UE avant !");
        return;
    }
    if (!fileGroupes.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier CSV";
        return;
    }
    QTextStream in(&fileGroupes);
    // Ignorer la première ligne (en-têtes)
    in.readLine();
    if (in.atEnd()){
        QMessageBox::warning(this, "Erreur", "Aucune ECUE disponible !");
        return;
    }
    SupprimerUEWindow *remUE = new SupprimerUEWindow();
    //connect(remUE, &SupprimerUEWindow::windowClosed, this, &MainWindow::refreshMainWindow);
    remUE->show();
}

// ------ Fenêtre "MAJ de l'EDT" --------

void MainWindow::updateEdt() {
    QFile fileECUE(QDir::currentPath() + "/../../CSV/Ecue.csv");
    if (!fileECUE.exists()) {
        QMessageBox::warning(this, "Erreur", "Veuillez créer une ECUE avant !");
        return;
    }
    if (!fileECUE.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier CSV";
        return;
    }
    QTextStream in(&fileECUE);
    // Ignorer la première ligne (en-têtes)
    in.readLine();
    if (in.atEnd()){
        QMessageBox::warning(this, "Erreur", "Aucune ECUE disponible !");
        return;
    }
    popupEdt *popup = new popupEdt();
    connect(popup, &popupEdt::windowClosed, this, &MainWindow::refreshMainWindow);
    popup->show();
}

// ------ Rafraichir la fenêtre principale après changement d'informations --------

void MainWindow::refreshMainWindow() {
    loadGroups(FALSE);
    onComboBoxSelectionChanged(groupComboBox->currentText());
}


// ------ Vérfier s'il y a au moins une ligne de données dans Enseignants.csv ou Groupes.csv --------

bool MainWindow::checkEnseignantsGroupesFiles() {

    // ------ Enseignants.csv vérification --------
    QFile fileEnseignants(QDir::currentPath() + "/../../CSV/" + "Enseignants.csv");
    if (!fileEnseignants.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream inEnseignants(&fileEnseignants);
    bool enseignantsDataFound = false;
    if (!inEnseignants.atEnd()) {
        inEnseignants.readLine();
    }
    while (!inEnseignants.atEnd()) {
        QString line = inEnseignants.readLine().trimmed();
        if (!line.isEmpty()) {
            QStringList columns = line.split(",");
            if (columns.size() >= 2) {
                enseignantsDataFound = true;
                break; // Données trouvées
            }
        }
    }
    fileEnseignants.close();

    if (!enseignantsDataFound) {
        return false;
    }

    // ------ Groupes.csv vérification --------
    QFile fileGroupes(QDir::currentPath() + "/../../CSV/" + "Groupes.csv");
    if (!fileGroupes.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream inGroupes(&fileGroupes);
    bool groupesDataFound = false;
    if (!inGroupes.atEnd()) {
        inGroupes.readLine();
    }
    while (!inGroupes.atEnd()) {
        QString line = inGroupes.readLine().trimmed();
        if (!line.isEmpty()) {
            groupesDataFound = true;
            break;
        }
    }
    fileGroupes.close();

    if (!groupesDataFound) {
        return false;
    }

    return true;
}

// ------ Vérfier s'il y a au moins une ligne de données dans Ecue.csv --------

bool MainWindow::checkECUEFile() {
    QFile fileEcue(QDir::currentPath() + "/../../CSV/" + "Ecue.csv");

    if (!fileEcue.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream inEcue(&fileEcue);
    bool ecueDataFound = false;

    if (!inEcue.atEnd()) {
        inEcue.readLine();
    }

    while (!inEcue.atEnd()) {
        QString line = inEcue.readLine().trimmed();
        if (!line.isEmpty()) {
            ecueDataFound = true;
            break;
        }
    }

    fileEcue.close();
    return ecueDataFound;
}


// ------ Chargement de Groupes.csv et Enseignant.csv (selon si la fenêtre a été ouverte pour la 1ere fois ou non) --------

void MainWindow::loadGroups(boolean firstTime) {
    QStringList filePaths = {
        QDir::currentPath() + "/../../CSV/" + "Groupes.csv",
        QDir::currentPath() + "/../../CSV/" + "Enseignants.csv"
    };

    QString currentGroup = groupComboBox->currentText();
    bool selectionExists = false;

    groupComboBox->clear();

    if (firstTime) {
        groupComboBox->addItem("Sélectionner");
    }

    for (const QString &filePath : filePaths) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            continue;
        }

        QTextStream in(&file);
        if (!firstTime || (firstTime && !in.atEnd())) {
            in.readLine();
        }

        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (!line.isEmpty()) {
                QString itemToAdd = line;
                if (filePath.contains("Enseignants.csv")) {
                    itemToAdd.replace(",", " ");
                }
                groupComboBox->addItem(itemToAdd);

                if (itemToAdd == currentGroup) {
                    selectionExists = true;
                }
            }
        }
        file.close();
    }

    if (!firstTime && selectionExists) {
        groupComboBox->setCurrentText(currentGroup);
    } else if (firstTime){
        groupComboBox->setCurrentIndex(0);
    }
}

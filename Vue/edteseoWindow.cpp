#include "edteseoWindow.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QLabel>

// Constructeur
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    setupActions();
    loadGroups();
    this->setFixedSize(880, 400);
    this->setWindowTitle("Emploi du temps");
}

void MainWindow::setupUI() {
    centralWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout *topBarLayout = new QHBoxLayout();

    QLabel *groupLabel = new QLabel("Groupe :", this);
    topBarLayout->addWidget(groupLabel);

    // Menu déroulant pour les groupes
    groupComboBox = new QComboBox(this);
    topBarLayout->addWidget(groupComboBox);

    topBarLayout->addStretch();

    // Bouton "-"
    remButton = new QPushButton("-", this);
    remButton->setFixedSize(25, 25); //
    topBarLayout->addWidget(remButton);

    remGroupButton = new QPushButton("Groupe", this);
    remECUEButton = new QPushButton("ECUE", this);

    remGroupButton->setVisible(false);
    remECUEButton->setVisible(false);

    topBarLayout->addWidget(remGroupButton);
    topBarLayout->addWidget(remECUEButton);


    // Bouton "+"
    addButton = new QPushButton("+", this);
    addButton->setFixedSize(25, 25);
    topBarLayout->addWidget(addButton);

    addGroupButton = new QPushButton("Groupe", this);
    addECUEButton = new QPushButton("ECUE", this);

    addGroupButton->setVisible(false);
    addECUEButton->setVisible(false);


    topBarLayout->addWidget(addGroupButton);
    topBarLayout->addWidget(addECUEButton);

    // Ajouter la barre supérieure au layout principal
    mainLayout->addLayout(topBarLayout);

    updateButton = new QPushButton("Mettre à jour l'emploi du temps", this);
    updateButton->setFixedWidth(200);  // Largeur du bouton

    // Créer un layout horizontal pour centrer le bouton
    QHBoxLayout *updateLayout = new QHBoxLayout();
    updateLayout->addWidget(updateButton, 0, Qt::AlignHCenter);  // Centrer horizontalement

    // Ajouter ce layout au layout principal
    mainLayout->addLayout(updateLayout);

    // Table
    setupTable();
    mainLayout->addWidget(table);

    setCentralWidget(centralWidget);
}

// Configuration de la table
void MainWindow::setupTable() {
    table = new QTableWidget(9, 8, this); // 5 lignes, 8 colonnes
    table->setHorizontalHeaderLabels({
        "Matière", "Enseignant", "H. totales", "H. CM",
        "H. TD", "H. Elec", "H. Info", "H. Exam"
    });
    table->setEditTriggers(QAbstractItemView::NoEditTriggers); // Interdire l'édition
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    table->setColumnWidth(0, 120); // Matière
    table->setColumnWidth(1, 120); // Enseignant
    table->setColumnWidth(2, 100); // Heures totales
    table->setColumnWidth(3, 100); // Heures CM
    table->setColumnWidth(4, 100); // Heures TD
    table->setColumnWidth(5, 100); // Heures Elec
    table->setColumnWidth(6, 100); // Heures Info
    table->setColumnWidth(7, 100); // Heures Exam
}

void MainWindow::setupActions() {
    connect(groupComboBox, &QComboBox::currentTextChanged, this, &MainWindow::onComboBoxSelectionChanged);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::toggleButtonsVisibility);
    connect(addGroupButton, &QPushButton::clicked, this, &MainWindow::addGroup);
    connect(addECUEButton, &QPushButton::clicked, this, &MainWindow::addECUE);

    connect(remButton, &QPushButton::clicked, this, &MainWindow::toggleRemButtonsVisibility);
    connect(remGroupButton, &QPushButton::clicked, this, &MainWindow::remGroup);
    connect(remECUEButton, &QPushButton::clicked, this, &MainWindow::remECUE);

    connect(updateButton, &QPushButton::clicked, this, &MainWindow::updateTimetable);
}

void MainWindow::onComboBoxSelectionChanged(const QString &selectedText) {
    for (int i = 0; i < table->rowCount(); ++i) {
        for (int j = 0; j < table->columnCount(); ++j) {
            table->setItem(i, j, new QTableWidgetItem("")); // Effacer les données des cellules
        }
    }

    QFile file(QDir::currentPath() + "/../../CSV/" + "Ecue.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible de charger le fichier Ecue.csv");
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

                    // Ajouter les heures par type de cours
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

                    // Remplir les colonnes non trouvées avec "0"
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


void MainWindow::toggleButtonsVisibility() {
    bool isVisible = addGroupButton->isVisible();
    addGroupButton->setVisible(!isVisible);
    addECUEButton->setVisible(!isVisible);
}

void MainWindow::toggleRemButtonsVisibility() {
    bool isVisible = remGroupButton->isVisible();
    remGroupButton->setVisible(!isVisible);
    remECUEButton->setVisible(!isVisible);
}


void MainWindow::loadGroups() {
    QStringList filePaths = {
        QDir::currentPath() + "/../../CSV/" + "Groupes.csv",
        QDir::currentPath() + "/../../CSV/" + "Enseignants.csv"
    };

    groupComboBox->clear();
    groupComboBox->addItem("Sélectionner");

    for (const QString &filePath : filePaths) {
        QFile file(filePath);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Erreur", "Impossible de charger le fichier : " + filePath);
            continue;
        }

        QTextStream in(&file);

        if (!in.atEnd()) {
            in.readLine();
        }

        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (!line.isEmpty()) {
                if (filePath.contains("Enseignants.csv")) {
                    line.replace(",", " ");
                }
                groupComboBox->addItem(line);
            }
        }

        file.close();
    }
}


void MainWindow::addGroup() {
    QMessageBox::information(this, "Ajout Groupe", "Fonctionnalité Ajouter Groupe appelée !");
}

void MainWindow::addECUE() {
    QMessageBox::information(this, "Ajout ECUE", "Fonctionnalité Ajouter ECUE appelée !");
}

void MainWindow::remGroup() {
    QMessageBox::information(this, "Suppression Groupe", "Fonctionnalité Supprimer Groupe appelée !");
}

void MainWindow::remECUE() {
    QMessageBox::information(this, "Suppression ECUE", "Fonctionnalité Supprimer ECUE appelée !");
}

void MainWindow::updateEdt() {
    QMessageBox::information(this, "Mise à jour", "Fonctionnalité MAJ EDT appelée !");
}

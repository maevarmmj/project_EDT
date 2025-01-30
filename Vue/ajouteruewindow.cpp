#include "ajouteruewindow.h"

AjouterUEWindow::AjouterUEWindow(QWidget *parent)
    : QMainWindow(parent) {
    setupUI();
    QString file(QDir::currentPath() + "/../../Ressources/planning.ico");
    QIcon icon(file);
    setWindowIcon(icon);
    this->setFixedSize(600, 400);
    this->setWindowTitle("Ajouter une UE");
    setWindowModality(Qt::ApplicationModal);
}


void AjouterUEWindow::setupUI(){
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);


    // ------------------ Message test ------------------------

    QStackedWidget *messageStack = new QStackedWidget(this);

    QLabel *TEST = new QLabel("Fonctionnalité bientôt disponible :)");
    TEST->setAlignment(Qt::AlignCenter);
    TEST->setStyleSheet("font-size: 14px; color: orange; font-weight: bold;");
    TEST->setFixedHeight(30);
    messageStack->addWidget(TEST);
    TEST->hide();

    // ------------------ Messages test ------------------------


    // Nom de l'UE
    QHBoxLayout *nomUELayout = new QHBoxLayout();
    ueLabel = new QLabel("Nom de l'UE : ");
    ueLineEdit = new QLineEdit();
    nomUELayout->addWidget(ueLabel);
    nomUELayout->addWidget(ueLineEdit);
    mainLayout->addLayout(nomUELayout);

    // GroupBox pour les cases à cocher des ECUE
    ecueGroupBox = new QGroupBox("ECUE à inclure", centralWidget);
    ecueGroupBox->setObjectName("ecueGroupBox");
    QVBoxLayout *ecueCheckBoxLayout = new QVBoxLayout(ecueGroupBox);
    ecueGroupBox->setLayout(ecueCheckBoxLayout);
    mainLayout->addWidget(ecueGroupBox);

    // ScrollArea pour les ECUE
    QScrollArea *scrollArea = new QScrollArea(centralWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(ecueGroupBox);
    mainLayout->addWidget(scrollArea);

    chargerEcueDepuisCSV();

    // Boutons Annuler et Enregistrer
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    annulerButton = new QPushButton("Annuler");
    enregistrerButton = new QPushButton("Enregistrer");
    buttonLayout->addWidget(annulerButton);
    buttonLayout->addWidget(enregistrerButton);
    mainLayout->addWidget(messageStack);
    mainLayout->addLayout(buttonLayout);

    connect(enregistrerButton, &QPushButton::clicked, this, &AjouterUEWindow::enregistrerUE);
    connect(annulerButton, &QPushButton::clicked, this, &AjouterUEWindow::annuler);
}

AjouterUEWindow::~AjouterUEWindow(){}


void AjouterUEWindow::chargerEcueDepuisCSV() {
    QString csvPath = QDir::currentPath() + "/../../CSV/Ecue.csv";
    QFile file(csvPath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier Ecue.csv:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    QString line;
    bool firstLine = true;
    while(in.readLineInto(&line)) {
        if (firstLine) {
            firstLine = false;
            continue;
        }
        QStringList fields = line.split(",");
        if (fields.size() >= 4) {
            QString ecueName = fields[0].trimmed();
            QString enseignantNom = fields[1].trimmed();
            QString enseignantPrenom = fields[2].trimmed();
            QString groupe = fields[3].trimmed();

            QString checkBoxText = QString("%1 (%2 %3, %4)")
                                       .arg(ecueName)
                                       .arg(enseignantNom)
                                       .arg(enseignantPrenom)
                                       .arg(groupe);
            QCheckBox *checkBox = new QCheckBox(checkBoxText);
            ecueCheckBoxes.append(checkBox);
            QVBoxLayout* layout = dynamic_cast<QVBoxLayout*>(ecueGroupBox->layout());
            if(layout) {
                layout->addWidget(checkBox);
            }
        }
    }
    file.close();
}

// ---- Quand on clique sur le bouton "Enregistrer" ----
void AjouterUEWindow::enregistrerUE(){
    QStackedWidget* messageStack = findChild<QStackedWidget*>();
    if (!messageStack) return;


    messageStack->setCurrentIndex(0);
    for (int i = 0; i < messageStack->count(); ++i) {
        QWidget* widget = messageStack->widget(i);
        if (widget) {
            if (i == 0) {
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

}


// ---- Quand on clique sur le bouton "annuler" ----
void AjouterUEWindow::annuler() {
    close();
}



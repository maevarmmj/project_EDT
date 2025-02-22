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
    TEST->setObjectName("bientot");
    TEST->setFixedHeight(30);
    messageStack->addWidget(TEST);
    TEST->hide();

    // ------------------ Messages test ------------------------


    QHBoxLayout *nomUELayout = new QHBoxLayout();
    ueLabel = new QLabel("Nom de l'UE : ");
    ueLineEdit = new QLineEdit();
    nomUELayout->addWidget(ueLabel);
    nomUELayout->addWidget(ueLineEdit);
    mainLayout->addLayout(nomUELayout);

    ecueGroupBox = new QGroupBox("ECUE à inclure", centralWidget);
    ecueGroupBox->setObjectName("ecueGroupBox");
    QVBoxLayout *ecueCheckBoxLayout = new QVBoxLayout(ecueGroupBox);
    ecueGroupBox->setLayout(ecueCheckBoxLayout);
    mainLayout->addWidget(ecueGroupBox);

    QScrollArea *scrollArea = new QScrollArea(centralWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(ecueGroupBox);
    scrollArea->setStyleSheet("background-color: transparent;");
    mainLayout->addWidget(scrollArea);

    chargerEcueDepuisCSV();

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    cancelButton = new QPushButton("Annuler");
    saveButton = new QPushButton("Enregistrer");
    cancelButton->setObjectName("cancelButton");
    saveButton->setObjectName("saveButton");
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(saveButton);
    mainLayout->addWidget(messageStack);
    mainLayout->addLayout(buttonLayout);

    connect(saveButton, &QPushButton::clicked, this, &AjouterUEWindow::enregistrerUE);
    connect(cancelButton, &QPushButton::clicked, this, &AjouterUEWindow::annuler);
}

AjouterUEWindow::~AjouterUEWindow(){}

// ------ Chargement de Ecue.csv" --------

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
            checkBox->setObjectName("cbText");
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



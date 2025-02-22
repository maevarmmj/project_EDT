#include "supprimeruewindow.h"


SupprimerUEWindow::SupprimerUEWindow(QWidget *parent)
    : QMainWindow(parent) {
    setupUI();
    QString file(QDir::currentPath() + "/../../Ressources/planning.ico");
    QIcon icon(file);
    setWindowIcon(icon);
    this->setWindowTitle("Supprimer une UE");
    setWindowModality(Qt::ApplicationModal);
}

void SupprimerUEWindow::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);

    // ------------------ Message test ------------------------

    QStackedWidget *messageStack = new QStackedWidget(this);

    QLabel *TEST = new QLabel("Fonctionnalité bientôt disponible :)");
    TEST->setAlignment(Qt::AlignCenter);
    TEST->setObjectName("bientot");
    TEST->setFixedHeight(30);
    messageStack->addWidget(TEST);
    TEST->hide();

    // ------------------ Messages test ------------------------


    // Label et ComboBox pour choisir l'UE à supprimer
    QHBoxLayout *ueLayout = new QHBoxLayout();
    ueLabel = new QLabel("UE à supprimer : ");
    ueLabel->setObjectName("titleLabel");
    ueComboBox = new QComboBox();
    ueLayout->addWidget(ueLabel);
    ueLayout->addWidget(ueComboBox);
    mainLayout->addLayout(ueLayout);


    // Boutons Annuler et Supprimer
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    annulerButton = new QPushButton("Annuler");
    supprimerButton = new QPushButton("Supprimer");
    buttonLayout->addWidget(annulerButton);
    buttonLayout->addWidget(supprimerButton);
    annulerButton->setObjectName("saveButton");
    supprimerButton->setObjectName("cancelButton");
    mainLayout->addWidget(messageStack);
    mainLayout->addLayout(buttonLayout);


    chargerUEDepuisCSV();
    connect(supprimerButton, &QPushButton::clicked, this, &SupprimerUEWindow::supprimerUE);
    connect(annulerButton, &QPushButton::clicked, this, &SupprimerUEWindow::annuler);
}


SupprimerUEWindow::~SupprimerUEWindow(){
}

void SupprimerUEWindow::chargerUEDepuisCSV() {
    QString csvPath = QDir::currentPath() + "/../../CSV/UE.csv";
    QFile file(csvPath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier UE.csv:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    QString line;
    while (in.readLineInto(&line)) {
        QStringList fields = line.split(",");
        if (fields.size() > 0) {
            QString ueName = fields[0].trimmed();
            ueComboBox->addItem(ueName);
        }
    }
    file.close();
}

// ---- Quand on clique sur le bouton "Supprimer" ----

void SupprimerUEWindow::supprimerUE() {
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
void SupprimerUEWindow::annuler() {
    close();
}

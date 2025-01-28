#include "popupsalleslibres.h"

PopupSallesLibres::PopupSallesLibres(const QList<int>& sallesLibres, QWidget *parent)
    : QDialog(parent), selectedRoomNumber(-1)
{
    setWindowTitle("Salles Libres");

    sallesComboBox = new QComboBox(this);
    for (int roomNumber : sallesLibres) {
        sallesComboBox->addItem(QString::number(roomNumber));
    }

    QPushButton *validerButton = new QPushButton("Valider", this);
    connect(validerButton, &QPushButton::clicked, this, &PopupSallesLibres::onValidationClicked);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(sallesComboBox);
    layout->addWidget(validerButton);

    setLayout(layout);
}

int PopupSallesLibres::getSelectedRoomNumber() const
{
    return selectedRoomNumber;
}

void PopupSallesLibres::onValidationClicked()
{
    selectedRoomNumber = sallesComboBox->currentText().toInt();
    emit roomSelected(selectedRoomNumber);
    accept(); // Ferme la fenêtre et indique que l'utilisateur a validé
}

#ifndef POPUPSALLESLIBRES_H
#define POPUPSALLESLIBRES_H

#include <QDialog>
#include <QComboBox>
#include <QVBoxLayout>
#include <QPushButton>

class PopupSallesLibres : public QDialog
{
    Q_OBJECT

public:
    PopupSallesLibres(const QList<int>& sallesLibres, QWidget *parent = nullptr);
    int getSelectedRoomNumber() const;

private:
    QComboBox *sallesComboBox;
    int selectedRoomNumber;

signals:
    void roomSelected(int roomNumber);

private slots:
    void onValidationClicked();
};

#endif // POPUPSALLESLIBRES_H

#ifndef POPUPSALLESLIBRES_H
#define POPUPSALLESLIBRES_H

#include <QDialog>
#include <QComboBox>
#include <QVBoxLayout>
#include <QPushButton>

class PopupSallesLibres : public QDialog
{
    Q_OBJECT

private:
    QComboBox *sallesComboBox;
    int selectedRoomNumber;

private slots:
    void onValidationClicked();
public:
    PopupSallesLibres(const QList<int>& sallesLibres, QWidget *parent = nullptr);
    int getSelectedRoomNumber() const;

signals:
    void roomSelected(int roomNumber);

};

#endif // POPUPSALLESLIBRES_H

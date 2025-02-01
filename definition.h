#ifndef DEFINITION_H
#define DEFINITION_H


#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QDateTime>
#include <QDebug>
#include <QDialog>
#include <QDir>
#include <QEnterEvent>
#include <QFile>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QMap>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QScrollArea>
#include <QSpinBox>
#include <QStackedWidget>
#include <QString>
#include <QStringList>
#include <QStyleFactory>
#include <QTableWidget>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include <string>


typedef enum cours {CM, TD, TP_INFO, TP_ELEC, EXAMEN} cours;
typedef enum boolean {FALSE, TRUE} boolean;

// ---- Pour savoir si la création a été réussie ou non ----
enum class CreationResult {
    Success,
    AlreadyExists,
    Error
};

// ---- Pour savoir si la suppression a été réussie ou non ----

enum class SuppressionResult {
    Success,
    Error
};

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

cours StrToCours(std::string coursStr) ;
std::string  CoursToStr(cours cours) ;


#endif // DEFINITION_H

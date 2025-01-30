#ifndef DEFINITION_H
#define DEFINITION_H

#include <string>
#include <QStringList>
#include <QIcon>
#include <QString>
#include <QLabel>
#include <QDebug>
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QDir>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QStyleFactory>
#include <QFile>
#include <QTextStream>
#include <QMap>
#include <QStackedWidget>
#include <QTimer>
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QSpinBox>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QStackedWidget>
#include <QTimer>
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QDir>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QScrollArea>
#include <QMessageBox>
#include <QStackedWidget>
#include <QTimer>
#include <QMainWindow>
#include <QTableWidget>
#include <QComboBox>
#include <QPushButton>
#include <QMenu>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QEnterEvent>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>
#include <QHBoxLayout>

#include <QApplication>
#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QComboBox>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDialog>
#include <QComboBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialog>
#include <QComboBox>
#include <QVBoxLayout>
#include <QPushButton>

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
#include <QStackedWidget>
#include <QTimer>

#include <QMainWindow>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QDir>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QStackedWidget>
#include <QTimer>

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QDir>
#include <QComboBox>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QStackedWidget>

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QSpinBox>
#include <QFormLayout>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QStackedWidget>

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QDir>
#include <QIcon>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QMessageBox>


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

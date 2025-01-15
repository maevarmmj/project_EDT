TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Model/enseignant.cpp \
        Model/groupeetudiant.cpp \
        Model/salle.cpp \
        main.cpp

HEADERS += \
    Model/enseignant.h \
    Model/groupeetudiant.h \
    Model/salle.h \



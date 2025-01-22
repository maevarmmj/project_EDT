TEMPLATE = app
CONFIG += c++17
CONFIG -= app_bundle
CONFIG += qt

QT += widgets
QT += sql

SOURCES += \
        Controlleur/CreneauControl.cpp \
        Model/creneau.cpp \
        Model/enseignant.cpp \
        Model/groupeetudiant.cpp \
        Model/salle.cpp \
        Model/ecue.cpp \
        Model/semaine.cpp \
        Model/edt.cpp \
        main.cpp

HEADERS += \
    Controlleur/CreneauControl.h \
    Model/creneau.h \
    Model/enseignant.h \
    Model/groupeetudiant.h \
    Model/salle.h \
    Model/ecue.h \
    Model/semaine.h \
    Model/edt.h \
    definition.h \
    main.h

DISTFILES += \
    reservations.db



TEMPLATE = app
CONFIG += c++17
CONFIG -= app_bundle
CONFIG += qt

QT += widgets
QT += sql

SOURCES += \
        Model/creneau.cpp \
        Model/enseignant.cpp \
        Model/groupeetudiant.cpp \
        Model/salle.cpp \
        Model/ecue.cpp \
        Model/semaine.cpp \
        Model/edt.cpp \
        Controleur/CreneauControl.cpp \
        controleur/grpeetudiantcontrolleur.cpp \
        main.cpp

HEADERS += \
    Model/creneau.h \
    Model/enseignant.h \
    Model/groupeetudiant.h \
    Model/salle.h \
    Model/ecue.h \
    Model/semaine.h \
    Model/edt.h \
    Controleur/CreneauControl.h \
    controleur/grpeetudiantcontrolleur.h \
    definition.h \
    main.h

DISTFILES += \
    reservations.db



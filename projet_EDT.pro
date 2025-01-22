TEMPLATE = app
CONFIG += c++17
CONFIG -= app_bundle
CONFIG += qt

QT += core widgets

SOURCES += \
        Controleur/SalleControl.cpp \
        Model/creneau.cpp \
        Model/enseignant.cpp \
        Model/groupeetudiant.cpp \
        Model/salle.cpp \
        Model/ecue.cpp \
        Model/semaine.cpp \
        Model/edt.cpp \
        Controleur/CreneauControl.cpp \
        controleur/grpeetudiantcontrolleur.cpp \
    controleur/ecuecontroleur.cpp \
        main.cpp

HEADERS += \
    Controleur/SalleControl.h \
    Model/creneau.h \
    Model/enseignant.h \
    Model/groupeetudiant.h \
    Model/salle.h \
    Model/ecue.h \
    Model/semaine.h \
    Model/edt.h \
    definition.h \
    controleur/ecuecontroleur.h \
    main.h

TEMPLATE = app
CONFIG += c++17
CONFIG -= app_bundle
CONFIG += qt

QT += core widgets
QT += sql

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
        Vue/popupEdt.cpp \
        Controleur/enseignantControl.cpp \
        Controleur/grpeetudiantcontrolleur.cpp \
        Controleur/ecuecontroleur.cpp \
        main.cpp

HEADERS += \
    Controleur/SalleControl.h \
    Controleur/enseignantControl.h \
    Model/creneau.h \
    Model/enseignant.h \
    Model/groupeetudiant.h \
    Model/salle.h \
    Model/ecue.h \
    Model/semaine.h \
    Model/edt.h \
    Vue/popupEdt.h \
    definition.h \
    Controleur/CreneauControl.h \
    Controleur/grpeetudiantcontrolleur.h \
    Controleur/ecuecontroleur.h \
    main.h

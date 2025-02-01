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
        Controleur/CreneauControl.cpp \
        Controleur/enseignantControl.cpp \
        Controleur/grpeetudiantcontrolleur.cpp \
        Controleur/ecuecontroleur.cpp \
        Vue/ajouteruewindow.cpp \
        Vue/popupEdt.cpp \
        Vue/edteseoWindow.cpp \
        Vue/supprimerEnseignantWindow.cpp \
        Vue/supprimerGroupeWindow.cpp \
        Vue/ajouterGroupeWindow.cpp \
        Vue/ajoutecueWindow.cpp \
        Vue/supprimerecuewindow.cpp \
        Vue/supprimerSalleWindow.cpp \
        Vue/supprimeruewindow.cpp \
        definition.cpp \
        main.cpp

HEADERS += \
    Controleur/SalleControl.h \
    Controleur/enseignantControl.h \
    Model/creneau.h \
    Model/enseignant.h \
    Model/groupeetudiant.h \
    Model/salle.h \
    Model/ecue.h \
    Vue/ajouteruewindow.h \
    Vue/popupEdt.h \
    Vue/edteseoWindow.h \
    Vue/ajouterGroupeWindow.h \
    Vue/supprimerEnseignantWindow.h \
    Vue/supprimerGroupeWindow.h \
    Vue/ajoutecueWindow.h \
    Vue/supprimerSalleWindow.h \
    Vue/supprimerecuewindow.h \
    Vue/supprimeruewindow.h \
    definition.h \
    Controleur/CreneauControl.h \
    Controleur/grpeetudiantcontrolleur.h \
    Controleur/ecuecontroleur.h \
    main.h

DISTFILES += \
    Ressources/StyleSheet.qss

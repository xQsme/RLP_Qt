#-------------------------------------------------
#
# Project created by QtCreator 2018-03-29T18:17:14
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RLP_Qt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    problem.cpp \
    population.cpp \
    individual.cpp \
    mainthread.cpp \
    multithread.cpp \
    dialogcustom.cpp \
    dialogbeecolony.cpp \
    dialogbeealgorithm.cpp \
    dialogantcolony.cpp \
    customalgorithm.cpp \
    geneticalgorithm.cpp

HEADERS += \
        mainwindow.h \
    problem.h \
    population.h \
    individual.h \
    mainthread.h \
    multithread.h \
    dialogcustom.h \
    dialogbeecolony.h \
    dialogbeealgorithm.h \
    dialogantcolony.h \
    customalgorithm.h \
    geneticalgorithm.h

FORMS += \
        mainwindow.ui \
    dialogcustom.ui \
    dialogbeecolony.ui \
    dialogbeealgorithm.ui \
    dialogantcolony.ui

DISTFILES += \
    qml.qml

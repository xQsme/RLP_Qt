#-------------------------------------------------
#
# Project created by QtCreator 2018-03-29T18:17:14
#
#-------------------------------------------------

QT       += core gui charts

CONFIG+= static

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
    customalgorithm.cpp \
    geneticalgorithm.cpp \
    customthread.cpp \
    antcolonyalgorithm.cpp \
    antcolonythread.cpp \
    beecolonyalgorithm.cpp \
    antcolonydialog.cpp \
    customdialog.cpp \
    custommultithread.cpp \
    beecolonydialog.cpp \
    beecolonythread.cpp \
    geneticdialog.cpp \
    geneticthread.cpp \
    beecolonymultithread.cpp \
    antcolonymultithread.cpp \
    geneticmultithread.cpp \
    customtestdialog.cpp \
    customtestmultithread.cpp \
    beecolonytestdialog.cpp \
    beecolonytestmultithread.cpp \
    genetictestdialog.cpp \
    genetictestmultithread.cpp \
    antcolonytestdialog.cpp \
    antcolonytestmultithread.cpp

HEADERS += \
        mainwindow.h \
    problem.h \
    population.h \
    individual.h \
    customalgorithm.h \
    geneticalgorithm.h \
    customthread.h \
    antcolonyalgorithm.h \
    antcolonythread.h \
    beecolonyalgorithm.h \
    beecolonythread.h \
    antcolonydialog.h \
    beecolonydialog.h \
    customdialog.h \
    custommultithread.h \
    geneticdialog.h \
    geneticthread.h \
    beecolonymultithread.h \
    antcolonymultithread.h \
    geneticmultithread.h \
    customtestdialog.h \
    customtestmultithread.h \
    beecolonytestdialog.h \
    beecolonytestmultithread.h \
    genetictestdialog.h \
    genetictestmultithread.h \
    antcolonytestdialog.h \
    antcolonytestmultithread.h

FORMS += \
        mainwindow.ui \
    antcolonydialog.ui \
    beecolonydialog.ui \
    customdialog.ui \
    geneticdialog.ui \
    customtestdialog.ui \
    beecolonytestdialog.ui \
    genetictestdialog.ui \
    antcolonytestdialog.ui

DISTFILES += \
    qml.qml

RC_FILE = app.rc

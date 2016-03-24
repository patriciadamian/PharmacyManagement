#-------------------------------------------------
#
# Project created by QtCreator 2015-06-03T18:04:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_pharmacy
TEMPLATE = app

CONFIG += c++14

SOURCES += main.cpp\
        mainwindow.cpp \
    Controller.cpp \
    FileRepository.cpp \
    Medicine.cpp

HEADERS  += mainwindow.h \
    Controller.h \
    FileRepository.h \
    InMemoryRepository.h \
    Medicine.h \
    MedicineValidator.h \
    Repository.h

FORMS    += mainwindow.ui

DISTFILES += \
    test.txt

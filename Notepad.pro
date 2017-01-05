#-------------------------------------------------
#
# Project created by QtCreator 2017-01-03T15:37:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Notepad
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    childwindow.cpp

HEADERS  += mainwindow.h \
    childwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

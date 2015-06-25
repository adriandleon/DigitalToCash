#-------------------------------------------------
#
# Project created by QtCreator 2015-06-24T11:24:53
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DigitalToCash
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    funciones.cpp \
    cashbox.cpp \
    dbhandler.cpp

HEADERS  += mainwindow.h \
    funciones.h \
    cashbox.h \
    dbhandler.h

FORMS    += mainwindow.ui

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
    cashbox.cpp \
    dbhandler.cpp \
    cardswindow.cpp \
    cashboxwindow.cpp

HEADERS  += mainwindow.h \
    cashbox.h \
    dbhandler.h \
    cardswindow.h \
    cashboxwindow.h

FORMS    += mainwindow.ui \
    cardswindow.ui \
    cashboxwindow.ui

RESOURCES += \
    recursos.qrc

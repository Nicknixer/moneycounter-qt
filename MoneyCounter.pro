#-------------------------------------------------
#
# Project created by QtCreator 2015-10-20T18:45:40
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MoneyCounter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    db.cpp

HEADERS  += mainwindow.h \
    db.h

FORMS    += mainwindow.ui

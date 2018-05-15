#-------------------------------------------------
#
# Project created by QtCreator 2018-05-15T08:29:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = studentManager
TEMPLATE = app


SOURCES += main.cpp\
        addstu.cpp \
    mainwindow.cpp \
    querystu.cpp

HEADERS  += addstu.h \
    mainwindow.h \
    querystu.h

FORMS    += addstu.ui \
    mainwindow.ui \
    querystu.ui

#-------------------------------------------------
#
# Project created by QtCreator 2019-12-05T01:13:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SPGraph_qt
TEMPLATE = app

CONFIG += c++17

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
        shapes/Circle.cpp \
        shapes/Ellipse.cpp \
        shapes/Helix.cpp \
        shapes/Shape.cpp \
        shapes/Text.cpp \
        shapes/TextInEllipse.cpp \
    newGraphDialog.cpp \
    nodeSelWidget.cpp \
    drawWidget.cpp \
    colorPicker.cpp \
    qhelix.cpp

HEADERS += \
        mainwindow.h \
        SPGraph/SPGraph.h \
        SPGraph/SPException.h \
        SPGraph/SPiterator.h \
        shapes/Circle.h \
        shapes/Ellipse.h \
        shapes/Helix.h \
        shapes/Shape.h \
        shapes/Text.h \
        shapes/TextInEllipse.h \
    custTreeItem.h \
    newGraphDialog.h \
    nodeSelWidget.h \
    drawWidget.h \
    colorPicker.h \
    qhelix.h

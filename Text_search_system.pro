#-------------------------------------------------
#
# Project created by QtCreator 2017-04-30T18:37:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Text_search_system
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG -= debug_and_release
DESTDIR = ./bin/release
MOC_DIR = ./build/release
OBJECTS_DIR = ./build/release
RCC_DIR = ./build/release
UI_DIR = ./build/release

SOURCES += main.cpp\
        mainwindow.cpp \
    src/SearchEngine.cpp

HEADERS  += mainwindow.h \
    src/SearchEngine.h

FORMS    += mainwindow.ui

DISTFILES += test/test.txt \
    Makefile.test \
    bin/test/2.txt \
    build/1.txt \
    .travis.yml \
    bin/test.txt

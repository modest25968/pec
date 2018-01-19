#-------------------------------------------------
#
# Project created by QtCreator 2017-12-12T20:04:16
#
#-------------------------------------------------

QT       += testlib
QT += widgets
QT += xml xmlpatterns

# QT       -= gui

TARGET = tst_testplayertest
CONFIG   += console
CONFIG   -= app_bundle

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
        tst_testplayertest.cpp \ 
    ../../src/backLoader/backloader.cpp \
    ../../src/core/xmlbasesong.cpp \
    ../../src/player/mnota.cpp \
    ../../src/player/msong.cpp \
    ../../src/player/player.cpp \
    ../../src/player/volcontroll.cpp \
    ../../src/player/volume_slider.cpp \
    ../../src/parser/parser.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../src/backLoader/backloader.h \
    ../../src/core/xmlbasesong.h \
    ../../src/player/mnota.h \
    ../../src/player/msong.h \
    ../../src/player/player.h \
    ../../src/player/volcontroll.h \
    ../../src/player/volume_slider.h \
    ../../src/parser/parser.h

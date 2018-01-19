#-------------------------------------------------
#
# Project created by QtCreator 2017-01-11T05:03:44
#
#-------------------------------------------------

QT       += testlib

#QT       -= gui
QT += widgets
QT += xml xmlpatterns

TARGET = tst_testopentest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_testopentest.cpp \
    ../../src/player/msong.cpp \
    ../../src/parser/parser.cpp \
    ../../src/player/mnota.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../src/player/msong.h \
    ../../src/parser/parser.h \
    ../../src/player/mnota.h

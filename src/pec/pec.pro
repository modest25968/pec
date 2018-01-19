#-------------------------------------------------
#
# Project created by QtCreator 2017-07-05T23:01:09
#
#-------------------------------------------------

QT       += core gui uiplugin

QT       += xml xmlpatterns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pe
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
#LIBS += C:\Users\User\Desktop\recroot\np\lib\fluidsynth\libfluidsynth.dll

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    ../player/mnota.cpp \
    ../player/msong.cpp \
    ../player/player.cpp \
    ../backLoader/backloader.cpp \
    ../player/volcontroll.cpp \
    qvolwidget.cpp \
    ../player/volume_slider.cpp \
    qsongscroll.cpp \
    ../parser/parser.cpp \
    ../songSelector/songselector.cpp

HEADERS += \
        mainwindow.h \
    ../player/mnota.h \
    ../player/msong.h \
    ../backLoader/backloader.h \
    ../player/player.h \
    ../player/volcontroll.h \
    qvolwidget.h \
    ../player/volume_slider.h \
    qsongscroll.h \
    ../parser/parser.h \
    ../songSelector/songselector.h

FORMS += \
        mainwindow.ui

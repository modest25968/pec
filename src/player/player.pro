#-------------------------------------------------
#
# Project created by QtCreator 2017-07-04T23:49:41
#
#-------------------------------------------------

QT       -= gui

TARGET = player
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        player.cpp \
    mnota.cpp \
    msong.cpp \
    volcontroll.cpp

HEADERS += \
        player.h \
    mnota.h \
    msong.h \
    ../core/abstractbackend.h \
    volcontroll.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../backLoader/release/ -lbackLoader
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../backLoader/debug/ -lbackLoader
else:unix: LIBS += -L$$OUT_PWD/../backLoader/ -lbackLoader

LIBS += -L$$OUT_PWD/../backLoader/debug/ -lbackLoader

INCLUDEPATH += $$PWD/../backLoader
DEPENDPATH += $$PWD/../backLoader

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../backLoader/release/libbackLoader.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../backLoader/debug/libbackLoader.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../backLoader/release/backLoader.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../backLoader/debug/backLoader.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../backLoader/libbackLoader.a


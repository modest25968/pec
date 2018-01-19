TEMPLATE = subdirs
QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-parameter

SUBDIRS += \
    src/pec \
    src/backLoader \
    src/fluidback \
    test/TestOpen \
    test/TestPlayer



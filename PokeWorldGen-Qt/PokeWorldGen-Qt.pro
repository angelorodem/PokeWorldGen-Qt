QT += widgets core gui

CONFIG += c++1z app

SOURCES += \
    main.cpp \
    world.cpp \
    generator.cpp \
    ../FastNoise/FastNoise.cpp \
    viewport.cpp

HEADERS += \
    world.h \
    generator.h \
    ../FastNoise/FastNoise.h \
    viewport.h

DISTFILES += \
    NOTAS


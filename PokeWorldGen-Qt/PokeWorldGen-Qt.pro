QT += widgets core gui

CONFIG += c++1z app

SOURCES += \
    main.cpp \
    world.cpp \
    sprite.cpp \
    generator.cpp \
    tile.cpp \
    ../FastNoise/FastNoise.cpp \
    viewport.cpp

HEADERS += \
    world.h \
    sprite.h \
    generator.h \
    tile.h \
    ../FastNoise/FastNoise.h \
    viewport.h

DISTFILES += \
    NOTAS


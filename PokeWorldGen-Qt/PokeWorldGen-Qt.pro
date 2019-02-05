QT += widgets core gui

CONFIG += c++1z console

SOURCES += \
    main.cpp \
    world.cpp \
    generator.cpp \
    ../FastNoise/FastNoise.cpp \
    viewport.cpp \
    tilesetbioma.cpp \
    tilepicker.cpp \
    janela_principal.cpp

HEADERS += \
    world.h \
    generator.h \
    ../FastNoise/FastNoise.h \
    viewport.h \
    tilesetbioma.h \
    tilepicker.h \
    janela_principal.h

DISTFILES += \
    NOTAS

FORMS += \
    tilepicker.ui \
    janela_principal.ui


QT += widgets core gui

CONFIG += c++1z console

QMAKE_CFLAGS += -fopenmp
QMAKE_CXXFLAGS += -fopenmp
QMAKE_CXXFLAGS_RELEASE += -Ofast -fomit-frame-pointer -fmodulo-sched -fmodulo-sched-allow-regmoves -fgcse-sm -fgcse-las -fgcse-after-reload -funsafe-loop-optimizations -flive-range-shrinkage -fsched-spec-load-dangerous -fsched2-use-superblocks -floop-nest-optimize -fprefetch-loop-arrays -ffinite-math-only -march=native -mtune=native -mfpmath="387+sse" -std=c++1z -static

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


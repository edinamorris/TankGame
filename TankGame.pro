QT -=gui
TARGET=TankGame
DESTDIR=./

SOURCES+=$$PWD/src/main.cpp \
         $$PWD/src/player.cpp \
         $$PWD/src/ai.cpp \
         $$PWD/src/turningPoint.cpp \
         $$PWD/src/bullet.cpp

HEADERS+=$$PWD/include/map.h \
         $$PWD/include/player.h \
         $$PWD/include/gamevalues.h \
         $$PWD/include/ai.h \
         $$PWD/include/turningPoint.h \
         $$PWD/include/bullet.h

INCLUDEPATH +=./include

cache()
QMAKE_CFLAGS+=-std=c99
QMAKE_CFLAGS+=$$system(sdl2-config  --cflags)
message(output from sdl2-config --cflags added to CXXFLAGS= $$QMAKE_CFLAGS)
INCLUDEPATH+=/usr/local/include/SDL2
LIBS+=$$system(sdl2-config  --libs)
message(output from sdl2-config --libs added to LIB=$$LIBS)
LIBS+=-lSDL2_image
macx:DEFINES+=MAC_OS_X_VERSION_MIN_REQUIRED=1060
CONFIG += console
CONFIG -= app_bundle

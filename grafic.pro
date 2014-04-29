TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

#SOURCES += main.cpp
SOURCES +=engine.cc
SOURCES +=Easyimage.cc
SOURCES +=ini_configuration.cc
SOURCES += grafic/primitives.cc

HEADERS += \
    primitives.h \
    grafic/primitives.h


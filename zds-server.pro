TEMPLATE = app
CONFIG += console c++11

CONFIG += qt

QT += core
QT += network

DESTDIR = ../bin

INCLUDEPATH += ./include

HEADERS += $$files(./include/*.h)
SOURCES += $$files(./src/*.cpp)

#-------------------------------------------------
#
# Project created by QtCreator 2011-11-08T04:58:54
#
#-------------------------------------------------
QT       += core gui \
            testlib \
            xml

TARGET = projet_c2a
TEMPLATE = app

OBJECTS_DIR = ../obj
MOC_DIR = $$OBJECTS_DIR
DEPENDPATH = $$OBJECTS_DIR

DESTDIR += ../release

INCLUDEPATH += ../include
HEADERSPATH = ../include

HEADERS  += $$HEADERSPATH/*.h

SOURCESPATH += ../src
SOURCES += $$SOURCESPATH/*.cpp

CONFIG += console

RESSOURCESPATH = ../ressources
RESOURCES += $$RESSOURCESPATH/c2a.qrc

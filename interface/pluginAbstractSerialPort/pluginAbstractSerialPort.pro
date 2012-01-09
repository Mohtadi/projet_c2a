QT       += core gui \
            qt3support


TEMPLATE = lib
CONFIG   += plugin

HEADERS  = ./*.h
SOURCES  = ./*.cpp
UI_DIR  += ./
FORMS    = cutecommdlg.ui

TARGET   = pluginSerialPort
DESTDIR += ./..

OBJECTS_DIR = ./../obj
MOC_DIR     = $$OBJECTS_DIR
DEPENDPATH  = $$OBJECTS_DIR

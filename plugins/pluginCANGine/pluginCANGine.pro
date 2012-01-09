TEMPLATE = lib
CONFIG   += plugin

TARGET   = pluginCANGine
DESTDIR += ./..

OBJECTS_DIR = ./../obj
MOC_DIR     = $$OBJECTS_DIR
DEPENDPATH  = $$OBJECTS_DIR

HEADERS     =  ./*.h \
               ../../interface/pluginAbstractSerialPort/*.h

INCLUDEPATH += ./*.h \
               ../../interface/pluginAbstractSerialPort/*.h

SOURCES     += ./*.cpp \
               ../../interface/pluginAbstractSerialPort/*.cpp

UI_DIR      += ../../interface/pluginAbstractSerialPort/
FORMS        = ../../interface/pluginAbstractSerialPort/cutecommdlg.ui


QT          += core gui

TEMPLATE = lib
CONFIG   += plugin

TARGET   = pluginBluetooth
DESTDIR += ./..

OBJECTS_DIR = ./../obj
MOC_DIR     = $$OBJECTS_DIR
DEPENDPATH  = $$OBJECTS_DIR

HEADERS     =   ./*.h \
                ../../interface/*.h \

INCLUDEPATH +=  ./*.h \
                ../../interface/*.h \


SOURCES     += ./*.cpp


QT          += core gui


LIBS += -L/usr/lib -lbluetooth \
        -L/usr/lib -lobexftp




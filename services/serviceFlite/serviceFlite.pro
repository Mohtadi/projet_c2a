TEMPLATE = lib
CONFIG   += plugin

TARGET   = serviceFlite

DESTDIR += ./..

OBJECTS_DIR = ./../obj
MOC_DIR     = $$OBJECTS_DIR
DEPENDPATH  = $$OBJECTS_DIR


HEADERS     =  ./*.h

INCLUDEPATH += ./*.h \
                /usr/include/flite/*.h
SOURCES     += ./*.cpp

QT          += core gui

LIBS += -L/usr/lib -lflite \
        -L/usr/lib -lflite_cmulex \
        -L/usr/lib -lflite_cmu_time_awb \
        -L/usr/lib -lflite_cmu_us_kal \
        -L/usr/lib -lflite_cmu_us_kal16 \
        -L/usr/lib -lflite_usenglish

#-------------------------------------------------
#
# Project created by QtCreator 2017-10-27T14:38:59
#
#-------------------------------------------------

QT       += core gui serialport 3dcore 3drender 3dinput

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Platform_XYZ_UI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    envelopetracker.cpp \
    envelope.cpp \
    manager3d.cpp \
    window.cpp \
    magnetestimator.cpp \
    magneticstructdata.cpp

HEADERS  += mainwindow.h \
    envelopetracker.h \
    envelope.h \
    manager3d.h \
    window.h \
    magnetestimator.h \
    magneticstructdata.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

INCLUDEPATH += "D:\Program Files\eigen"

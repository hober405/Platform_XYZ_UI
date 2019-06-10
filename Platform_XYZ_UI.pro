#-------------------------------------------------
#
# Project created by QtCreator 2017-10-27T14:38:59
#
#-------------------------------------------------

QT       += core gui serialport # 3dcore 3drender 3dinput 3dextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14
TARGET = Platform_XYZ_UI
TEMPLATE = app

CONFIG += link_pkgconfig
PKGCONFIG += roscpp \
    tf

SOURCES += main.cpp\
        mainwindow.cpp \
    envelopetracker.cpp \
    envelope.cpp \
#    manager3d.cpp \
#    window.cpp \
    magnetestimator.cpp \
    magneticdatapreprocessor.cpp \
    turtletfreceiver.cpp \
    mgncalibration.cpp \
    dialogcalibrate.cpp

HEADERS  += mainwindow.h \
    envelopetracker.h \
    envelope.h \
#    manager3d.h \
#    window.h \
    magnetestimator.h \
    magneticdatapreprocessor.h \
    turtletfreceiver.h \
    mgncalibration.h \
    dialogcalibrate.h

FORMS    += mainwindow.ui \
    dialogcalibrate.ui

RESOURCES += \
    resources.qrc

INCLUDEPATH += /usr/include/eigen3 \
    /opt/ros/kinetic/include

DEPENDPATH += /opt/ros/kinetic/include

#LIBS += -L /opt/ros/kinetic/lib

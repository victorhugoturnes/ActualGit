TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    linkedlist.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    linkedlist.h


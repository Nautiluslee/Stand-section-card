#-------------------------------------------------
#
# Project created by QtCreator 2016-11-17T15:06:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = screen
TEMPLATE = app


SOURCES += main.cpp\
        screen.cpp \
    mylabel.cpp \
    arrivedstation.cpp \
    nextstation.cpp \
    switchstations.cpp \
    imitate.cpp \
    universdata.cpp

HEADERS  += screen.h \
    mylabel.h \
    arrivedstation.h \
    nextstation.h \
    switchstations.h \
    imitate.h \
    universdata.h

FORMS    += screen.ui \
    arrivedstation.ui \
    nextstation.ui \
    switchstations.ui

LIBS += /home/lyj/qt-app/lib/libipc_usocket.a

RESOURCES += \
    icons.qrc

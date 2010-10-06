#-------------------------------------------------
#
# Project created by QtCreator 2010-09-28T12:41:19
#
#-------------------------------------------------

QT       += core gui

TARGET = WywFilm
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

wince*: {
   DEPLOYMENT_PLUGIN += qjpeg qmng qgif qpng
}

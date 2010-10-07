#-------------------------------------------------
#
# Project created by QtCreator 2010-09-28T12:41:19
#
#-------------------------------------------------

QT       += core gui
QT       += phonon

TARGET = WywFilm
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

wince*: {
   DEPLOYMENT_PLUGIN += qjpeg qmng qgif qpng
}

wince*{
DEPLOYMENT_PLUGIN += phonon_ds9 phonon_waveout
}

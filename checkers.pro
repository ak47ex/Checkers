#-------------------------------------------------
#
# Project created by QtCreator 2016-03-04T18:37:52
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = checkers
TEMPLATE = app

LIBS += -lopengl32
SOURCES += main.cpp\
        gamewindow.cpp \
    field.cpp

HEADERS  += gamewindow.h \
    field.h \
    piece.h

FORMS    += gamewindow.ui

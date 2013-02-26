#-------------------------------------------------
#
# Project created by QtCreator 2012-01-25T19:20:45
#
#-------------------------------------------------

QT       += core gui

TARGET = cam
TEMPLATE = app

# include(../common.pro)

QMAKE_CXXFLAGS += -g

SOURCES += *.cpp

HEADERS  += dialog_drill.h  pp_base.h  pp_drill.h  dialog_contour.h  pp_contour.h  

FORMS    += *.ui

INCLUDEPATH    += ../librecad/src/plugins  ../librecad/src/lib/engine ../librecad/src/lib/debug 
INCLUDEPATH += /usr/lib/qt4/include/QtCore /usr/lib/qt4/include/QtGui

OBJECTS_DIR = intermediate
MOC_DIR = intermediate
RCC_DIR = intermediate
TS_DIR = intermediate
UI_DIR = intermediate
UI_HERADERS_DIR = intermediate
UI_SOURCES_DIR = intermediate

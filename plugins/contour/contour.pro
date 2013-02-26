#-------------------------------------------------
#
# Project created by QtCreator 2011-03-22T19:33:11
#
#-------------------------------------------------

QT       += gui
TEMPLATE = lib
CONFIG += plugin
VERSION = 1.0.1
PLUGIN_NAME=contour

GENERATED_DIR = ../../generated/plugin/sameprop

# Use common project definitions.
include(../../common.pro)

# For plugins
INCLUDEPATH    += ../../librecad/src/plugins  ../../librecad/src/lib/engine ../../librecad/src/lib/debug 


SOURCES += contour.cpp   ../../cam/filenames.cpp

HEADERS += contour.h


# DLLDESTDIR = ../../unix/resources/plugins/

win32 {
    Debug {
        DLLDESTDIR = ../../debug/resources/plugins
        TARGET = $$PLUGIN_NAME

    } else {
        DLLDESTDIR = ../../release/resources/plugins
        TARGET = $$PLUGIN_NAME
    }
}
unix {
    macx { 
	TARGET = ../../LibreCAD.app/Contents/Resources/plugins/$$PLUGIN_NAME
    }
    else { 
	TARGET = ../../unix/resources/plugins/$$PLUGIN_NAME
    }
}




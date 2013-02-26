#-------------------------------------------------
#
# Project created by QtCreator 2012-01-22T10:17:32
#
#-------------------------------------------------

QT       += core gui


TEMPLATE = lib
CONFIG += plugin
VERSION = 1.0.1
PLUGIN_NAME=entities_to_layers

# Use common project definitions.
include(../../common.pro)

GENERATED_DIR = ../../generated/plugin/sameprop
INCLUDEPATH    += ../../librecad/src/plugins  ../../librecad/src/lib/engine ../../librecad/src/lib/debug 

SOURCES += entities_to_layers.cpp 

HEADERS  += entities_to_layers.h

FORMS    += 

# ------------------------------------


# DLLDESTDIR = ../../unix/resources/plugins/
win32 {
        DLLDESTDIR = ../../windows/resources/plugins
        TARGET = $$PLUGIN_NAME
}
unix {
    macx { 
	TARGET = ../../LibreCAD.app/Contents/Resources/plugins/$$PLUGIN_NAME
    }
    else { 
	TARGET = ../../unix/resources/plugins/$$PLUGIN_NAME
    }
}

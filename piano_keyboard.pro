#-------------------------------------------------
#
# Project created by QtCreator 2012-04-29T18:20:45
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = piano_keyboard
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -lportmidi -lX11 -lXtst

SOURCES += main.cpp \
    Midi_parser.cpp \
    Note.cpp \
    Midi_reader.cpp

HEADERS += \
    Midi_parser.h \
    Note.h \
    Midi_reader.h

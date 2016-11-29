QT += core
QT -= gui

CONFIG += c++11

TARGET = TolvuFolk
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    notendaui.cpp \
    tolvufolk.cpp \
    tolvufolkservice.cpp

HEADERS += \
    notendaui.h \
    tolvufolk.h \
    tolvufolkservice.h

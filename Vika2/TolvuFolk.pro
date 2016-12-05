QT += core
QT -= gui
QT += sql

CONFIG += c++11

TARGET = TolvuFolk
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    notendaui.cpp \
    tolvufolk.cpp \
    tolvufolkservice.cpp \
    sqltenging.cpp \
    velar.cpp

HEADERS += \
    notendaui.h \
    tolvufolk.h \
    tolvufolkservice.h \
    sqltenging.h \
    velar.h

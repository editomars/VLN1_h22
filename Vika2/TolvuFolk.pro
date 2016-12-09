QT += core
QT -= gui
QT += sql

INCLUDEPATH += /models
INCLUDEPATH += /services
INCLUDEPATH += /sql
INCLUDEPATH += /ui

CONFIG += c++11

TARGET = TolvuFolk
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ui/notendaui.cpp \
    models/tolvufolk.cpp \
    services/tolvufolkservice.cpp \
    sql/sqltenging.cpp \
    models/velar.cpp \
    services/velarservice.cpp

HEADERS += \
    ui/notendaui.h \
    models/tolvufolk.h \
    services/tolvufolkservice.h \
    sql/sqltenging.h \
    models/velar.h \
    services/velarservice.h

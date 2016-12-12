#-------------------------------------------------
#
# Project created by QtCreator 2016-12-12T13:01:11
#
#-------------------------------------------------

QT       += core gui sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vika3
TEMPLATE = app

INCLUDEPATH += /models
INCLUDEPATH += /services
INCLUDEPATH += /sql
INCLUDEPATH += /ui

SOURCES += main.cpp\
        adalgluggi.cpp \
    models/tolvufolk.cpp \
    models/velar.cpp \
    services/tolvufolkservice.cpp \
    services/velarservice.cpp \
    sql/sqltenging.cpp

HEADERS  += adalgluggi.h \
    models/tolvufolk.h \
    models/velar.h \
    services/tolvufolkservice.h \
    services/velarservice.h \
    sql/sqltenging.h

FORMS    += adalgluggi.ui

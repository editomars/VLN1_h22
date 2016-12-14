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
INCLUDEPATH += /dialogues

SOURCES += main.cpp\
        adalgluggi.cpp \
    models/tolvufolk.cpp \
    models/velar.cpp \
    services/tolvufolkservice.cpp \
    services/velarservice.cpp \
    sql/sqltenging.cpp \
    dialogues/addscientist.cpp \
    dialogues/uppfaerafolkgluggi.cpp \
    dialogues/uppfaeravelgluggi.cpp \
    dialogues/addmachine.cpp

HEADERS  += adalgluggi.h \
    models/tolvufolk.h \
    models/velar.h \
    services/tolvufolkservice.h \
    services/velarservice.h \
    sql/sqltenging.h \
    dialogues/addscientist.h \
    dialogues/uppfaerafolkgluggi.h \
    dialogues/uppfaeravelgluggi.h \
    dialogues/addmachine.h \
    utils/enums.h \
    utils/constants.h

FORMS    += adalgluggi.ui \
    dialogues/addscientist.ui \
    dialogues/uppfaerafolkgluggi.ui \
    dialogues/uppfaeravelgluggi.ui \
    dialogues/addmachine.ui

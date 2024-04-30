TEMPLATE = app
QT+=sql\
        widgets \
        core gui

CONFIG += c++11 console
CONFIG -= app_bundle

QT += sql

SOURCES += \
        dbmanager.cpp \
        graphic.cpp \
        main.cpp

HEADERS += \
    dbmanager.h \
    graphic.h

INCLUDEPATH += D:/SQLite3

LIBS += -LD:/SQLite3 -lsqlite3

DISTFILES += \
    people.db

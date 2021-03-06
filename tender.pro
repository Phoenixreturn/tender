#-------------------------------------------------
#
# Project created by QtCreator 2018-04-14T15:42:34
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tender
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS "MAXBUFFERSIZE=4096" QUERIES=\\\":/statements\\\"

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    database.cpp \
    treeitem.cpp \
    treemodel.cpp \
    customcombobox.cpp \
    projectclass.cpp \
    comboboxdelegate.cpp \
    pgqueryitemdelegate.cpp \
    tableitem.cpp \
    tablemodel.cpp

HEADERS += \
        mainwindow.h \
    database.h \
    treeitem.h \
    treemodel.h \
    customcombobox.h \
    projectclass.h \
    comboboxdelegate.h \
    pgqueryitemdelegate.h \
    tableitem.h \
    tablemodel.h \
    deselectabletreeview.h

FORMS += \
        mainwindow.ui

DISTFILES += \
    .gitignore \
    queries.sql

RESOURCES += \
    tender.qrc

#-------------------------------------------------
#
# Project created by QtCreator 2015-11-09T23:33:46
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jira-rest-client
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    NetworkService.cpp \
    Project.cpp \
    ProjectButton.cpp

HEADERS  += MainWindow.h \
    NetworkService.h \
    Project.h \
    ProjectButton.h

FORMS    += MainWindow.ui

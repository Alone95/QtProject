#-------------------------------------------------
#
# Project created by QtCreator 2016-10-10T22:59:17
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ConDatabase
TEMPLATE = app
SOURCES += main.cpp             \
           mainwindow.cpp       \
           cmysplashscreen.cpp  \
           login.cpp            \
           registeruser.cpp     \
           qpasswordlineedit.cpp\
           completelineedit.cpp \
    filetreeview.cpp \
    dispdata.cpp

HEADERS  += mainwindow.h \
    cmysplashscreen.h \
    login.h \
    registeruser.h \
    qpasswordlineedit.h \
    completelineedit.h \
    completelineedit.h \
    filetreeview.h \
    dispdata.h


FORMS    += mainwindow.ui \
    login.ui \
    registeruser.ui

RESOURCES += \
    myresources.qrc
RC_FILE +=icon.rc

#-------------------------------------------------
#
# Project created by QtCreator 2015-09-03T11:07:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChessS3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chessboardwidget.cpp \
    piece.cpp \
    player.cpp \
    position.cpp \
    board.cpp \
    move.cpp \
    playercontroller.cpp

HEADERS  += mainwindow.h \
    chessboardwidget.h \
    enums.h \
    piece.h \
    player.h \
    position.h \
    board.h \
    move.h \
    playercontroller.h

FORMS    += mainwindow.ui

OTHER_FILES +=

RESOURCES += \
    Images.qrc
